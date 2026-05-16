import fs from "node:fs/promises";
import path from "node:path";
import { fileURLToPath } from "node:url";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const profilePath = path.join(root, "data", "profile.json");
const profile = JSON.parse(await fs.readFile(profilePath, "utf8"));
const pdfName = profile.portfolio?.resume_output_pdf || path.basename(profile.portfolio?.resume_pdf_path || "curriculo.pdf");
const source = path.join(root, "dist", pdfName);
const target = path.join(root, "public", "dist", pdfName);

await fs.access(source);
await fs.mkdir(path.dirname(target), { recursive: true });
await fs.copyFile(source, target);

console.log(`PDF publico atualizado: ${path.relative(root, target)}`);
