import { chromium } from "playwright";
import path from "node:path";
import fs from "node:fs";
import { fileURLToPath } from "node:url";

const projectRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const distHtml = path.join(projectRoot, "dist", "cv.html");
const dataPath = path.join(projectRoot, "data", "profile.json");
const data = JSON.parse(fs.readFileSync(dataPath, "utf8"));
const outputFileName = data?.portfolio?.resume_output_pdf || "cv.pdf";
const outPdf = path.join(projectRoot, "dist", outputFileName);

if (!fs.existsSync(distHtml)) {
  console.error("dist/cv.html não existe. Rode: npm run build");
  process.exit(1);
}

const html = fs.readFileSync(distHtml, "utf8");
const baseUrl = `file://${path.dirname(distHtml)}/`;

const browser = await chromium.launch();
const page = await browser.newPage();

await page.setContent(html, { waitUntil: "load", baseURL: baseUrl });

await page.pdf({
  path: outPdf,
  format: "A4",
  printBackground: true,
  margin: { top: "0.5in", right: "0.5in", bottom: "0.5in", left: "0.5in" },
});

await browser.close();
console.log(`Gerado: ${path.relative(projectRoot, outPdf)}`);
