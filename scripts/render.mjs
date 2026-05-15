import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const projectRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const templatePath = path.join(projectRoot, "templates", "ats.html");
const cssPath = path.join(projectRoot, "templates", "style.css");
const dataPath = path.join(projectRoot, "data", "profile.json");
const distDir = path.join(projectRoot, "dist");

fs.mkdirSync(distDir, { recursive: true });

const tpl = fs.readFileSync(templatePath, "utf8");
const css = fs.readFileSync(cssPath, "utf8");
const data = JSON.parse(fs.readFileSync(dataPath, "utf8"));

function escapeHtml(s) {
  return String(s ?? "")
    .replaceAll("&", "&amp;")
    .replaceAll("<", "&lt;")
    .replaceAll(">", "&gt;")
    .replaceAll('"', "&quot;");
}

function toArray(value) {
  return Array.isArray(value) ? value : [];
}

function skillsHtml(skills) {
  return toArray(skills)
    .map((g) => {
      const items = toArray(g?.items).join(", ");
      return `<div class="item"><div class="item-title">${escapeHtml(g?.group)}:</div> ${escapeHtml(
        items,
      )}</div>`;
    })
    .join("\n");
}

function bulletsHtml(bullets) {
  const list = toArray(bullets);
  if (list.length === 0) return "";
  return `<ul class="bullets">${list.map((b) => `<li>${escapeHtml(b)}</li>`).join("")}</ul>`;
}

function projectsHtml(projects) {
  return toArray(projects)
    .map((p) => {
      const links = toArray(p?.links)
        .map(
          (l) => {
            const url = escapeHtml(l?.url);
            return `<li>${escapeHtml(l?.label)}: <a href="${url}" target="_blank" rel="noopener noreferrer">${url}</a></li>`;
          },
        )
        .join("");
      const stackLine = p?.stack
        ? `<div class="tech-line">Stack: ${escapeHtml(p.stack)}</div>`
        : "";
      const description = p?.description
        ? `<p class="summary">${escapeHtml(p.description)}</p>`
        : "";
      const bullets = bulletsHtml(p?.bullets);
      return `
<div class="item">
  <div class="item-title">${escapeHtml(p?.title)}</div>
  ${stackLine}
  ${description}
  ${bullets}
  ${links ? `<ul class="bullets">${links}</ul>` : ""}
</div>`;
    })
    .join("\n");
}

function experienceHtml(exps) {
  return toArray(exps)
    .map((e) => {
      const bullets = bulletsHtml(e?.bullets);
      return `
<div class="item">
  <div class="item-header">
    <div>
      <div class="item-title">${escapeHtml(e?.role)}</div>
      <div class="item-subtitle">${escapeHtml(e?.company)}</div>
    </div>
    <div class="item-date">${escapeHtml(e?.date)}</div>
  </div>
  ${bullets}
</div>`;
    })
    .join("\n");
}

function educationHtml(eds) {
  return toArray(eds)
    .map(
      (e) => `
<div class="item">
  <div class="item-header">
    <div>
      <div class="item-title">${escapeHtml(e?.title)}</div>
      <div class="item-subtitle">${escapeHtml(e?.subtitle)}</div>
    </div>
    <div class="item-date">${escapeHtml(e?.date)}</div>
  </div>
</div>`,
    )
    .join("\n");
}

function languagesHtml(langs) {
  return toArray(langs)
    .map((l) => {
      const level = l?.level ? ` — ${escapeHtml(l.level)}` : "";
      const note = l?.note ? escapeHtml(l.note) : "";
      return `
<div class="item">
  <div class="item-header">
    <div class="item-title">${escapeHtml(l?.name)}${level}</div>
    <div class="item-date">${note}</div>
  </div>
</div>`;
    })
    .join("\n");
}

const html = tpl
  .replace(
    `<link rel="stylesheet" href="./style.css" />`,
    `<style>${css}</style>`,
  )
  .replaceAll("{{NAME}}", escapeHtml(data.name))
  .replaceAll("{{TITLE}}", escapeHtml(data.title))
  .replaceAll("{{EMAIL}}", escapeHtml(data.email))
  .replaceAll("{{PHONE_E164}}", escapeHtml(data.phone_e164))
  .replaceAll("{{PHONE_DISPLAY}}", escapeHtml(data.phone_display))
  .replaceAll("{{LOCATION}}", escapeHtml(data.location))
  .replaceAll("{{LINKEDIN_URL}}", escapeHtml(data.linkedin_url))
  .replaceAll("{{GITHUB_URL}}", escapeHtml(data.github_url))
  .replaceAll("{{WEBSITE_URL}}", escapeHtml(data.website_url))
  .replaceAll("{{LINKEDIN_TEXT}}", escapeHtml(data.linkedin_text))
  .replaceAll("{{GITHUB_TEXT}}", escapeHtml(data.github_text))
  .replaceAll("{{WEBSITE_TEXT}}", escapeHtml(data.website_text))
  .replaceAll("{{SUMMARY}}", escapeHtml(data.summary))
  .replaceAll("{{SKILLS_HTML}}", skillsHtml(data.skills))
  .replaceAll("{{PROJECTS_HTML}}", projectsHtml(data.projects))
  .replaceAll("{{EXPERIENCE_HTML}}", experienceHtml(data.experience))
  .replaceAll("{{EDUCATION_HTML}}", educationHtml(data.education))
  .replaceAll("{{LANGUAGES_HTML}}", languagesHtml(data.languages));

const outHtml = path.join(distDir, "cv.html");
fs.writeFileSync(outHtml, html, "utf8");
console.log(`Gerado: ${path.relative(projectRoot, outHtml)}`);
