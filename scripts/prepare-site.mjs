import fs from "node:fs/promises";
import path from "node:path";
import { fileURLToPath } from "node:url";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const siteDir = path.join(root, "dist", "site");
const profileSource = path.join(root, "data", "profile.json");
const profileTarget = path.join(siteDir, "data", "profile.json");

async function copyRequired(source, target, label) {
  try {
    await fs.access(source);
  } catch {
    throw new Error(`${label} não encontrado em ${path.relative(root, source)}`);
  }

  await fs.mkdir(path.dirname(target), { recursive: true });
  await fs.copyFile(source, target);
  console.log(`Copiado: ${path.relative(root, target)}`);
}

const profile = JSON.parse(await fs.readFile(profileSource, "utf8"));
const pdfName = profile.portfolio?.resume_output_pdf || path.basename(profile.portfolio?.resume_pdf_path || "curriculo.pdf");

await copyRequired(profileSource, profileTarget, "profile.json");
await copyRequired(path.join(root, "dist", "cv.html"), path.join(siteDir, "dist", "cv.html"), "cv.html");
await copyRequired(path.join(root, "dist", pdfName), path.join(siteDir, "dist", pdfName), pdfName);
