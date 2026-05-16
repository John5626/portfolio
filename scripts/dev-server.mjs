import http from "node:http";
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { spawn } from "node:child_process";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const port = Number(process.argv[2] || process.env.PORT || 5500);
const host = process.env.HOST || "127.0.0.1";
const profilePath = path.join(root, "data", "profile.json");
const editorEnabled = process.env.EDITOR_ENABLED === "true" || process.env.VITE_ENABLE_EDITOR === "true";
const maxBodyBytes = 8 * 1024 * 1024;

const types = {
  ".css": "text/css; charset=utf-8",
  ".html": "text/html; charset=utf-8",
  ".js": "text/javascript; charset=utf-8",
  ".json": "application/json; charset=utf-8",
  ".pdf": "application/pdf",
  ".png": "image/png",
  ".jpg": "image/jpeg",
  ".jpeg": "image/jpeg",
  ".webp": "image/webp",
  ".svg": "image/svg+xml",
};

function resolveRequest(url) {
  const parsed = new URL(url, `http://${host}:${port}`);
  const decoded = decodeURIComponent(parsed.pathname);
  const requested = decoded === "/" ? "/index.html" : decoded;
  const filePath = path.resolve(root, `.${requested}`);

  if (!filePath.startsWith(root)) {
    return null;
  }

  return filePath;
}

function sendJson(res, status, body) {
  res.writeHead(status, {
    "Content-Type": "application/json; charset=utf-8",
    "Cache-Control": "no-store",
  });
  res.end(JSON.stringify(body, null, 2));
}

function readBody(req) {
  return new Promise((resolve, reject) => {
    let body = "";

    req.on("data", (chunk) => {
      body += chunk;
      if (body.length > maxBodyBytes) {
        req.destroy();
        reject(new Error("Payload muito grande"));
      }
    });
    req.on("end", () => resolve(body));
    req.on("error", reject);
  });
}

async function readJsonBody(req) {
  const body = await readBody(req);
  return JSON.parse(body || "{}");
}

function runNodeScript(scriptName) {
  return new Promise((resolve) => {
    const child = spawn(process.execPath, [path.join(root, "scripts", scriptName)], {
      cwd: root,
      shell: false,
    });
    let stdout = "";
    let stderr = "";

    child.stdout.on("data", (chunk) => {
      stdout += chunk;
    });
    child.stderr.on("data", (chunk) => {
      stderr += chunk;
    });
    child.on("close", (code) => {
      resolve({ code, stdout: stdout.trim(), stderr: stderr.trim() });
    });
  });
}

async function handleApi(req, res, pathname) {
  try {
    if (!editorEnabled && (
      (pathname === "/api/profile" && req.method === "PUT")
      || (pathname === "/api/build" && req.method === "POST")
      || (pathname === "/api/pdf" && req.method === "POST")
      || (pathname === "/api/upload-profile-image" && req.method === "POST")
    )) {
      sendJson(res, 403, { error: "Editor desabilitado neste ambiente." });
      return true;
    }

    if (pathname === "/api/profile" && req.method === "GET") {
      const data = JSON.parse(await fs.promises.readFile(profilePath, "utf8"));
      sendJson(res, 200, data);
      return true;
    }

    if (pathname === "/api/profile" && req.method === "PUT") {
      const data = await readJsonBody(req);
      if (!data || typeof data !== "object" || Array.isArray(data)) {
        sendJson(res, 400, { error: "Perfil inválido" });
        return true;
      }

      const next = `${JSON.stringify(data, null, 2)}\n`;
      await fs.promises.writeFile(profilePath, next, "utf8");
      sendJson(res, 200, { ok: true, file: "data/profile.json" });
      return true;
    }

    if (pathname === "/api/upload-profile-image" && req.method === "POST") {
      const data = await readJsonBody(req);
      const dataUrl = String(data?.dataUrl || "");
      const match = dataUrl.match(/^data:(image\/(?:png|jpeg|webp));base64,([a-zA-Z0-9+/=]+)$/);

      if (!match) {
        sendJson(res, 400, { error: "Imagem inválida. Use PNG, JPG ou WebP." });
        return true;
      }

      const extensionByMime = {
        "image/png": "png",
        "image/jpeg": "jpg",
        "image/webp": "webp",
      };
      const extension = extensionByMime[match[1]];
      const buffer = Buffer.from(match[2], "base64");

      if (!buffer.length || buffer.length > 4 * 1024 * 1024) {
        sendJson(res, 400, { error: "A imagem deve ter até 4 MB." });
        return true;
      }

      const uploadDir = path.join(root, "public", "uploads");
      const fileName = `profile-${Date.now()}.${extension}`;
      const filePath = path.join(uploadDir, fileName);
      await fs.promises.mkdir(uploadDir, { recursive: true });
      await fs.promises.writeFile(filePath, buffer);
      sendJson(res, 200, { ok: true, path: `/uploads/${fileName}` });
      return true;
    }

    if (pathname === "/api/build" && req.method === "POST") {
      const result = await runNodeScript("render.mjs");
      sendJson(res, result.code === 0 ? 200 : 500, result);
      return true;
    }

    if (pathname === "/api/pdf" && req.method === "POST") {
      const pdfResult = await runNodeScript("export-pdf.mjs");
      if (pdfResult.code !== 0) {
        sendJson(res, 500, pdfResult);
        return true;
      }

      const syncResult = await runNodeScript("sync-pdf.mjs");
      sendJson(res, syncResult.code === 0 ? 200 : 500, {
        code: syncResult.code,
        stdout: [pdfResult.stdout, syncResult.stdout].filter(Boolean).join("\n"),
        stderr: [pdfResult.stderr, syncResult.stderr].filter(Boolean).join("\n"),
      });
      return true;
    }

    if (pathname.startsWith("/api/")) {
      sendJson(res, 404, { error: "Endpoint não encontrado" });
      return true;
    }
  } catch (error) {
    sendJson(res, 500, { error: error.message });
    return true;
  }

  return false;
}

const server = http.createServer(async (req, res) => {
  const parsed = new URL(req.url || "/", `http://${host}:${port}`);
  if (await handleApi(req, res, parsed.pathname)) {
    return;
  }

  const filePath = resolveRequest(req.url || "/");

  if (!filePath) {
    res.writeHead(403);
    res.end("Forbidden");
    return;
  }

  if (!editorEnabled && path.basename(filePath).toLowerCase() === "admin.html") {
    res.writeHead(404);
    res.end("Not found");
    return;
  }

  fs.readFile(filePath, (error, content) => {
    if (error) {
      res.writeHead(error.code === "ENOENT" ? 404 : 500);
      res.end(error.code === "ENOENT" ? "Not found" : "Server error");
      return;
    }

    res.writeHead(200, {
      "Content-Type": types[path.extname(filePath)] || "application/octet-stream",
      "Cache-Control": "no-store",
    });
    res.end(content);
  });
});

server.listen(port, host, () => {
  console.log(`Servidor local disponível em http://${host}:${port}/`);
  console.log(`API disponível em http://${host}:${port}/api/profile`);
  console.log(editorEnabled ? "Editor local habilitado." : "Editor local desabilitado.");
});
