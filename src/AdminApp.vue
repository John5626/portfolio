<script setup lang="ts">
import { onMounted, ref } from "vue";
import { editorEnabled } from "./editorAccess";
import type { Profile, Project } from "./types";

const profile = ref<Profile | null>(null);
const status = ref("Carregando data/profile.json...");
const isSaving = ref(false);

function toArray<T>(value: T[] | null | undefined): T[] {
  return Array.isArray(value) ? value : [];
}

function splitComma(value: string): string[] {
  return value.split(",").map((item) => item.trim()).filter(Boolean);
}

function splitLines(value: string): string[] {
  return value.split("\n").map((item) => item.trim()).filter(Boolean);
}

function linkText(project: Project): string {
  return toArray(project.links).map((link) => `${link.label || ""} | ${link.url || ""}`).join("\n");
}

function setLinks(project: Project, value: string) {
  project.links = splitLines(value).map((line) => {
    const [label, ...urlParts] = line.split("|");
    return {
      label: String(label || "").trim(),
      url: urlParts.join("|").trim(),
    };
  }).filter((link) => link.label || link.url);
}

async function api<T>(path: string, options: RequestInit = {}): Promise<T> {
  const response = await fetch(path, {
    headers: { "Content-Type": "application/json", ...(options.headers || {}) },
    ...options,
  });
  const data = await response.json();
  if (!response.ok) {
    throw new Error(data.error || data.stderr || `HTTP ${response.status}`);
  }
  return data;
}

async function loadProfile() {
  status.value = "Carregando data/profile.json...";
  profile.value = await api<Profile>("/api/profile");
  status.value = "Perfil carregado.";
}

async function saveProfile() {
  if (!profile.value) return;
  isSaving.value = true;
  status.value = "Salvando data/profile.json...";
  try {
    await api("/api/profile", {
      method: "PUT",
      body: JSON.stringify(profile.value),
    });
    status.value = "Perfil salvo em data/profile.json.";
  } finally {
    isSaving.value = false;
  }
}

async function runAction(path: string, label: string) {
  status.value = `${label}...`;
  const result = await api<{ stdout?: string; stderr?: string }>(path, {
    method: "POST",
    body: "{}",
  });
  status.value = [result.stdout, result.stderr].filter(Boolean).join("\n") || `${label} concluído.`;
}

function addSkill() {
  profile.value?.skills.push({ group: "", items: [] });
}

function addExperience() {
  profile.value?.experience.push({ role: "", company: "", date: "", location: "", bullets: [] });
}

function addEducation() {
  profile.value?.education.push({ title: "", subtitle: "", date: "" });
}

function addLanguage() {
  profile.value?.languages.push({ name: "", note: "" });
}

function addProject() {
  profile.value?.projects.push({
    title: "",
    type: "",
    stack: "",
    description: "",
    tags: [],
    icon: "",
    icon_class: "",
    links: [],
  });
}

function removeAt<T>(items: T[], index: number) {
  items.splice(index, 1);
}

function restoreTheme() {
  document.body.classList.add("dark");
}

onMounted(() => {
  restoreTheme();
  if (!editorEnabled) {
    status.value = "Editor desabilitado neste ambiente.";
    return;
  }
  loadProfile().catch((error) => {
    status.value = `Erro ao carregar: ${error.message}`;
  });
});
</script>

<template>
  <header id="header">
    <a class="logo" href="/">João<span>.dev</span>_</a>
    <nav id="nav-desktop">
      <a href="/">portfolio</a>
      <a href="/dist/cv.html" target="_blank" rel="noopener">cv.html</a>
      <a href="/dist/curriculo_JSOUZA.pdf" target="_blank" rel="noopener">pdf</a>
    </nav>
    <div class="header-actions" v-if="editorEnabled">
      <button class="theme-btn" type="button" :disabled="isSaving" @click="saveProfile">[ salvar ]</button>
      <button class="theme-btn" type="button" @click="loadProfile">[ recarregar ]</button>
    </div>
  </header>

  <main v-if="!editorEnabled" class="editor-shell restricted-shell">
    <section class="editor-section restricted-card">
      <div class="section-label">restricted</div>
      <h1>Edição desabilitada</h1>
      <p>Esta tela não fica disponível no build de produção. Use o ambiente local de desenvolvimento para editar os dados do portfólio.</p>
      <a class="restricted-link" href="/">Voltar ao portfólio</a>
    </section>
  </main>

  <main v-else class="editor-shell">
    <aside class="editor-sidebar">
      <div class="section-label">editor</div>
      <h1>Dados do portfólio</h1>
      <nav class="editor-tabs" aria-label="Seções de edição">
        <a href="#personal">dados</a>
        <a href="#summary">resumo</a>
        <a href="#skills">skills</a>
        <a href="#experience">experiência</a>
        <a href="#education">formação</a>
        <a href="#languages">idiomas</a>
        <a href="#projects">projetos</a>
        <a href="#portfolio">portfolio</a>
      </nav>
      <div class="editor-actions">
        <button type="button" @click="runAction('/api/build', 'Gerando HTML')">Gerar HTML</button>
        <button type="button" @click="runAction('/api/pdf', 'Gerando PDF')">Gerar PDF</button>
      </div>
      <pre id="status" class="status">{{ status }}</pre>
    </aside>

    <form v-if="profile" id="profile-form" class="editor-form" @submit.prevent>
      <section id="personal" class="editor-section">
        <div class="section-label">profile</div>
        <h2 class="sec-title">Dados pessoais</h2>
        <div class="form-grid two">
          <label>Nome completo <input v-model="profile.name" type="text" /></label>
          <label>Nome curto <input v-model="profile.display_name" type="text" /></label>
          <label>Título ATS <input v-model="profile.title" type="text" /></label>
          <label>Título curto <input v-model="profile.short_title" type="text" /></label>
          <label>E-mail <input v-model="profile.email" type="email" /></label>
          <label>Telefone E.164 <input v-model="profile.phone_e164" type="text" /></label>
          <label>Telefone exibido <input v-model="profile.phone_display" type="text" /></label>
          <label>Localização <input v-model="profile.location" type="text" /></label>
          <label>LinkedIn texto <input v-model="profile.linkedin_text" type="text" /></label>
          <label>LinkedIn URL <input v-model="profile.linkedin_url" type="url" /></label>
          <label>GitHub texto <input v-model="profile.github_text" type="text" /></label>
          <label>GitHub URL <input v-model="profile.github_url" type="url" /></label>
          <label>Lattes texto <input v-model="profile.website_text" type="text" /></label>
          <label>Lattes URL <input v-model="profile.website_url" type="url" /></label>
        </div>
      </section>

      <section id="summary" class="editor-section">
        <div class="section-label">about</div>
        <h2 class="sec-title">Resumo</h2>
        <label>Resumo profissional <textarea v-model="profile.summary" rows="8"></textarea></label>
      </section>

      <section id="skills" class="editor-section">
        <div class="section-heading">
          <div>
            <div class="section-label">skills</div>
            <h2 class="sec-title">Skills</h2>
          </div>
          <button type="button" @click="addSkill">Adicionar grupo</button>
        </div>
        <div class="repeat-list">
          <div class="repeat-item" v-for="(skill, index) in profile.skills" :key="index">
            <div class="repeat-title">
              <strong>Grupo de skill {{ index + 1 }}</strong>
              <button type="button" @click="removeAt(profile.skills, index)">Remover</button>
            </div>
            <div class="form-grid two">
              <label>Grupo <input v-model="skill.group" type="text" /></label>
              <label>Itens <input :value="skill.items.join(', ')" type="text" @input="skill.items = splitComma(($event.target as HTMLInputElement).value)" /></label>
            </div>
          </div>
        </div>
      </section>

      <section id="experience" class="editor-section">
        <div class="section-heading">
          <div>
            <div class="section-label">career</div>
            <h2 class="sec-title">Experiência</h2>
          </div>
          <button type="button" @click="addExperience">Adicionar experiência</button>
        </div>
        <div class="repeat-list">
          <div class="repeat-item" v-for="(item, index) in profile.experience" :key="index">
            <div class="repeat-title">
              <strong>Experiência {{ index + 1 }}</strong>
              <button type="button" @click="removeAt(profile.experience, index)">Remover</button>
            </div>
            <div class="form-grid two">
              <label>Cargo <input v-model="item.role" type="text" /></label>
              <label>Empresa <input v-model="item.company" type="text" /></label>
              <label>Data <input v-model="item.date" type="text" /></label>
              <label>Local <input v-model="item.location" type="text" /></label>
            </div>
            <label>Bullets <textarea :value="item.bullets.join('\n')" rows="5" @input="item.bullets = splitLines(($event.target as HTMLTextAreaElement).value)"></textarea></label>
          </div>
        </div>
      </section>

      <section id="education" class="editor-section">
        <div class="section-heading">
          <div>
            <div class="section-label">education</div>
            <h2 class="sec-title">Formação</h2>
          </div>
          <button type="button" @click="addEducation">Adicionar formação</button>
        </div>
        <div class="repeat-list">
          <div class="repeat-item" v-for="(item, index) in profile.education" :key="index">
            <div class="repeat-title">
              <strong>Formação {{ index + 1 }}</strong>
              <button type="button" @click="removeAt(profile.education, index)">Remover</button>
            </div>
            <div class="form-grid two">
              <label>Título <input v-model="item.title" type="text" /></label>
              <label>Instituição <input v-model="item.subtitle" type="text" /></label>
              <label>Data <input v-model="item.date" type="text" /></label>
            </div>
          </div>
        </div>
      </section>

      <section id="languages" class="editor-section">
        <div class="section-heading">
          <div>
            <div class="section-label">languages</div>
            <h2 class="sec-title">Idiomas</h2>
          </div>
          <button type="button" @click="addLanguage">Adicionar idioma</button>
        </div>
        <div class="repeat-list">
          <div class="repeat-item" v-for="(item, index) in profile.languages" :key="index">
            <div class="repeat-title">
              <strong>Idioma {{ index + 1 }}</strong>
              <button type="button" @click="removeAt(profile.languages, index)">Remover</button>
            </div>
            <div class="form-grid two">
              <label>Nome <input v-model="item.name" type="text" /></label>
              <label>Nota <input v-model="item.note" type="text" /></label>
            </div>
          </div>
        </div>
      </section>

      <section id="projects" class="editor-section">
        <div class="section-heading">
          <div>
            <div class="section-label">work</div>
            <h2 class="sec-title">Projetos</h2>
          </div>
          <button type="button" @click="addProject">Adicionar projeto</button>
        </div>
        <div class="repeat-list">
          <div class="repeat-item" v-for="(project, index) in profile.projects" :key="index">
            <div class="repeat-title">
              <strong>Projeto {{ index + 1 }}</strong>
              <button type="button" @click="removeAt(profile.projects, index)">Remover</button>
            </div>
            <div class="form-grid two">
              <label>Título <input v-model="project.title" type="text" /></label>
              <label>Tipo <input v-model="project.type" type="text" /></label>
              <label>Stack <input v-model="project.stack" type="text" /></label>
              <label>Tags <input :value="project.tags.join(', ')" type="text" @input="project.tags = splitComma(($event.target as HTMLInputElement).value)" /></label>
              <label>Ícone <input v-model="project.icon" type="text" /></label>
              <label>Classe do ícone <input v-model="project.icon_class" type="text" /></label>
            </div>
            <label>Descrição <textarea v-model="project.description" rows="4"></textarea></label>
            <label>Links <textarea :value="linkText(project)" rows="4" @input="setLinks(project, ($event.target as HTMLTextAreaElement).value)"></textarea></label>
          </div>
        </div>
      </section>

      <section id="portfolio" class="editor-section">
        <div class="section-label">site</div>
        <h2 class="sec-title">Portfolio</h2>
        <div class="form-grid two">
          <label>Usuário terminal <input v-model="profile.portfolio.terminal_user" type="text" /></label>
          <label>Nome no logo <input v-model="profile.portfolio.logo_name" type="text" /></label>
          <label>Comando do hero <input v-model="profile.portfolio.command" type="text" /></label>
          <label>Foco <input :value="profile.portfolio.focus.join(', ')" type="text" @input="profile.portfolio.focus = splitComma(($event.target as HTMLInputElement).value)" /></label>
          <label>Status <input v-model="profile.portfolio.status" type="text" /></label>
          <label>Iniciais <input v-model="profile.portfolio.profile_initials" type="text" /></label>
          <label>Label do perfil <input v-model="profile.portfolio.profile_label" type="text" /></label>
          <label>Caminho PDF <input v-model="profile.portfolio.resume_pdf_path" type="text" /></label>
          <label>Caminho HTML <input v-model="profile.portfolio.resume_html_path" type="text" /></label>
          <label>Nome de download <input v-model="profile.portfolio.resume_download_name" type="text" /></label>
          <label>Arquivo PDF gerado <input v-model="profile.portfolio.resume_output_pdf" type="text" /></label>
          <label>Ano <input v-model="profile.portfolio.copyright_year" type="text" /></label>
          <label>Stack do rodapé <input :value="profile.portfolio.footer_stack.join(', ')" type="text" @input="profile.portfolio.footer_stack = splitComma(($event.target as HTMLInputElement).value)" /></label>
        </div>
      </section>
    </form>
  </main>
</template>
