<script setup lang="ts">
import { computed, nextTick, onMounted, onUnmounted, ref } from "vue";
import { editorEnabled } from "./editorAccess";
import { firstName, loadProfile, profileUrl, toArray, uniqueSkills } from "./profile";
import type { Profile } from "./types";

type Drop = {
  x: number;
  y: number;
  speed: number;
  word: string;
  color: string;
};

const profile = ref<Profile | null>(null);
const error = ref("");
const isDark = ref(true);
const menuOpen = ref(false);
const canvas = ref<HTMLCanvasElement | null>(null);
let drops: Drop[] = [];
let timer = 0;

const snippets = [
  "<?php", "namespace App", "use Illuminate", "class Controller",
  "Route::get", "Route::post", "Request $request", "return response()",
  "php artisan", "make:model", "make:migration", "Eloquent",
  "Schema::create", "$table->id()", "Auth::user()", "Validator::make",
  "public function", "private function", "protected $fillable",
  "Model::query()", "where()", "first()", "get()", "paginate()",
  "try {", "catch (Exception)", "DB::transaction", "composer install",
  "SELECT *", "WHERE id =", "INNER JOIN", "ORDER BY", "FOREIGN KEY",
  "MySQL", "MariaDB", "API REST", "HTTP 200", "JSON", "LGPD",
  "git commit", "git branch", "git push", "Vue.createApp",
  "ref()", "computed()", "watch()", "v-model", "axios.get",
  "async", "await", "const ", "return", "{}", "[]", "===",
  "npm install", "vite", "clean code", "feature", "deploy",
];

const skillMeta: Record<string, { icon: string; className: string; level: string }> = {
  php: { icon: "PHP", className: "php", level: "Intermediário" },
  laravel: { icon: "Lv", className: "laravel", level: "Intermediário" },
  "apis rest": { icon: "API", className: "rest", level: "Iniciante" },
  "api rest": { icon: "API", className: "rest", level: "Iniciante" },
  mysql: { icon: "My", className: "mysql", level: "Intermediário" },
  sql: { icon: "SQL", className: "sql", level: "Intermediário" },
  mariadb: { icon: "Md", className: "mariadb", level: "Iniciante" },
  "vue.js": { icon: "Vue", className: "vue", level: "Iniciante" },
  "vue.js 3": { icon: "Vue", className: "vue", level: "Iniciante" },
  git: { icon: "Git", className: "git", level: "Iniciante" },
};

const focus = computed(() => {
  if (!profile.value) return [];
  return toArray(profile.value.portfolio?.focus).length
    ? profile.value.portfolio.focus
    : uniqueSkills(profile.value).slice(0, 3);
});

const skills = computed(() => {
  if (!profile.value) return [];
  return uniqueSkills(profile.value).map((skill) => {
    const key = skill.trim().toLowerCase();
    return {
      name: skill,
      ...(skillMeta[key] || { icon: skill.slice(0, 3), className: "rest", level: "Conhecimento" }),
    };
  });
});

const heroStats = computed(() => {
  if (!profile.value) return [];
  return [
    { value: `${skills.value.length}`, label: "stacks" },
    { value: `${toArray(profile.value.projects).length}`, label: "projetos" },
    { value: `${toArray(profile.value.experience).length}`, label: "frentes" },
  ];
});

const featuredProject = computed(() => {
  if (!profile.value) return null;
  return toArray(profile.value.projects)[0] || null;
});

const currentExperience = computed(() => {
  if (!profile.value) return null;
  return toArray(profile.value.experience)[0] || null;
});

const timeline = computed(() => {
  if (!profile.value) return [];
  const experiences = toArray(profile.value.experience).map((item) => ({
    year: item.date,
    title: `${item.role}${item.company ? ` — ${item.company}` : ""}`,
    desc: toArray(item.bullets).slice(0, 2).join(" "),
  }));
  const education = toArray(profile.value.education).map((item) => ({
    year: item.date,
    title: item.title,
    desc: item.subtitle,
  }));
  return [...experiences, ...education];
});

const contacts = computed(() => {
  if (!profile.value) return [];
  return [
    { label: "E-mail", icon: "@", url: `mailto:${profile.value.email}` },
    { label: "GitHub", icon: "⊙", url: profile.value.github_url },
    { label: "LinkedIn", icon: "in", url: profile.value.linkedin_url },
    { label: "Lattes", icon: "CV", url: profile.value.website_url },
  ].filter((contact) => contact.url);
});

const terminalUser = computed(() => {
  if (!profile.value) return "portfolio";
  return profile.value.portfolio?.terminal_user || firstName(profile.value).toLowerCase();
});

const logoName = computed(() => {
  if (!profile.value) return "portfolio";
  return profile.value.portfolio?.logo_name || firstName(profile.value);
});

function normalizeTheme() {
  document.body.classList.toggle("dark", isDark.value);
}

function toggleTheme() {
  isDark.value = !isDark.value;
  localStorage.setItem("theme", isDark.value ? "dark" : "light");
  normalizeTheme();
  initMatrix();
}

function closeMenu() {
  menuOpen.value = false;
}

function initMatrix() {
  const el = canvas.value;
  if (!el) return;
  el.width = el.offsetWidth;
  el.height = el.offsetHeight;
  drops = [];

  const colors = isDark.value
    ? ["rgba(204,153,205,0.85)", "rgba(126,198,153,0.85)", "rgba(232,197,104,0.85)", "rgba(140,140,140,0.75)"]
    : ["rgba(0,51,179,0.95)", "rgba(6,125,23,0.95)", "rgba(110,63,154,0.95)", "rgba(140,140,140,0.75)"];

  const cols = Math.floor(el.width / 32);
  for (let i = 0; i < cols; i += 1) {
    const copies = 1 + (Math.random() < 0.45 ? 1 : 0) + (Math.random() < 0.15 ? 1 : 0);
    for (let j = 0; j < copies; j += 1) {
      drops.push({
        x: i * 32 + Math.random() * 12,
        y: Math.random() * -el.height,
        speed: 0.65 + Math.random() * 1.05,
        word: snippets[Math.floor(Math.random() * snippets.length)],
        color: colors[Math.floor(Math.random() * colors.length)],
      });
    }
  }
}

function drawMatrix() {
  const el = canvas.value;
  const ctx = el?.getContext("2d");
  if (!el || !ctx) return;

  ctx.clearRect(0, 0, el.width, el.height);
  ctx.font = "14px JetBrains Mono, monospace";
  ctx.textBaseline = "top";
  ctx.shadowColor = "rgba(255, 255, 255, 0.12)";
  ctx.shadowBlur = 0.5;

  drops.forEach((drop) => {
    ctx.fillStyle = drop.color;
    ctx.fillText(drop.word, drop.x, drop.y);
    drop.y += drop.speed;
    if (drop.y > el.height + 20) {
      drop.y = -20;
      drop.word = snippets[Math.floor(Math.random() * snippets.length)];
      drop.speed = 0.65 + Math.random() * 1.05;
    }
  });
}

function onScroll() {
  const sections = document.querySelectorAll("section[id]");
  const navLinks = document.querySelectorAll("nav#nav-desktop a");
  let current = "";

  sections.forEach((section) => {
    const top = (section as HTMLElement).offsetTop - 80;
    if (window.scrollY >= top) current = section.id;
  });

  navLinks.forEach((link) => {
    (link as HTMLElement).style.color = link.getAttribute("href") === `#${current}` ? "var(--accent)" : "";
  });
}

function setupScrollReveal() {
  if (!("IntersectionObserver" in window)) return;
  const observer = new IntersectionObserver(
    (entries) => {
      entries.forEach((entry) => {
        if (entry.isIntersecting) {
          const el = entry.target as HTMLElement;
          el.style.opacity = "1";
          el.style.transform = "translateY(0)";
        }
      });
    },
    { threshold: 0.1 },
  );

  document.querySelectorAll(".tl-item, .stack-card, .proj-card, .contact-link").forEach((el) => {
    const item = el as HTMLElement;
    item.style.opacity = "0";
    item.style.transform = "translateY(16px)";
    item.style.transition = "opacity 0.5s ease, transform 0.5s ease";
    observer.observe(item);
  });
}

onMounted(async () => {
  isDark.value = localStorage.getItem("theme") !== "light";
  normalizeTheme();

  try {
    profile.value = await loadProfile();
    document.title = `${profile.value.display_name || profile.value.name} | Dev PHP`;
    document
      .querySelector('meta[name="description"]')
      ?.setAttribute("content", `Portfólio de ${profile.value.name} — ${profile.value.short_title || profile.value.title}`);
    await nextTick();
    setupScrollReveal();
  } catch (err) {
    error.value = err instanceof Error ? err.message : String(err);
  }

  initMatrix();
  timer = window.setInterval(drawMatrix, 45);
  window.addEventListener("resize", initMatrix);
  window.addEventListener("scroll", onScroll, { passive: true });
});

onUnmounted(() => {
  window.clearInterval(timer);
  window.removeEventListener("resize", initMatrix);
  window.removeEventListener("scroll", onScroll);
});
</script>

<template>
  <header id="header">
    <div class="logo">{{ logoName }}<span>.dev</span>_</div>
    <nav id="nav-desktop">
      <a href="#banner">~/home</a>
      <a href="#sobre">sobre</a>
      <a href="#stacks">stacks</a>
      <a href="#trajetoria">trajetória</a>
      <a href="#projetos">projetos</a>
      <a href="#contato">contato</a>
      <a v-if="editorEnabled" href="/admin.html">editar</a>
    </nav>
    <div class="header-actions">
      <button class="theme-btn" type="button" @click="toggleTheme">
        <span class="theme-dot"></span>
        {{ isDark ? "light" : "dark" }}
      </button>
      <button class="hamburger" type="button" @click="menuOpen = !menuOpen">☰</button>
    </div>
  </header>

  <div class="nav-mobile" :class="{ open: menuOpen }">
    <a href="#banner" @click="closeMenu">~/home</a>
    <a href="#sobre" @click="closeMenu">sobre</a>
    <a href="#stacks" @click="closeMenu">stacks</a>
    <a href="#trajetoria" @click="closeMenu">trajetória</a>
    <a href="#projetos" @click="closeMenu">projetos</a>
    <a href="#contato" @click="closeMenu">contato</a>
    <a v-if="editorEnabled" href="/admin.html" @click="closeMenu">editar</a>
  </div>

  <section id="banner">
    <canvas id="matrix-canvas" ref="canvas"></canvas>
    <div class="banner-grid">
      <template v-if="profile">
        <div class="banner-content">
          <div class="status-pill">
            <span class="status-led"></span>
            {{ profile.portfolio.status }}
          </div>
          <div class="prompt-line">
            <span class="user">{{ terminalUser }}@dev</span>:~$&nbsp;<span class="cmd">{{ profile.portfolio.command }}</span>
          </div>
          <h1 class="main-title">
            &gt; Olá, eu sou<br />
            <span class="name-highlight">{{ profile.display_name || profile.name }}</span><span class="cursor"></span>
          </h1>
          <p class="subtitle">
            <span class="kw">const</span> role = <span class="str">"{{ profile.short_title || profile.title }}"</span><br />
            <span class="kw">const</span> focus =
            <template v-for="(item, index) in focus" :key="item">
              <span class="str">"{{ item }}"</span><span v-if="index < focus.length - 1"> | </span>
            </template>
          </p>
          <div class="hero-actions">
            <a :href="profile.portfolio.resume_pdf_path" :download="profile.portfolio.resume_download_name" class="dl-btn">Baixar currículo</a>
            <a :href="profile.github_url" target="_blank" rel="noopener" class="ghost-btn">Ver GitHub</a>
          </div>
          <div class="hero-stats" aria-label="Resumo do perfil">
            <div class="stat-item" v-for="stat in heroStats" :key="stat.label">
              <strong>{{ stat.value }}</strong>
              <span>{{ stat.label }}</span>
            </div>
          </div>
        </div>
        <aside class="hero-console" aria-label="Resumo em formato de editor">
          <div class="console-top">
            <span></span>
            <span></span>
            <span></span>
            <strong>portfolio.ts</strong>
          </div>
          <div class="console-tabs">
            <span class="active">index.php</span>
            <span>api.ts</span>
            <span>profile.json</span>
          </div>
          <div class="code-lines">
            <p><span class="line-no">01</span><span class="kw">export default</span> &#123;</p>
            <p><span class="line-no">02</span>&nbsp;&nbsp;dev: <span class="str">"{{ profile.display_name || profile.name }}"</span>,</p>
            <p><span class="line-no">03</span>&nbsp;&nbsp;role: <span class="str">"{{ profile.short_title || profile.title }}"</span>,</p>
            <p><span class="line-no">04</span>&nbsp;&nbsp;stack: [
              <template v-for="(item, index) in focus" :key="`console-${item}`">
                <span class="str">"{{ item }}"</span><span v-if="index < focus.length - 1">, </span>
              </template>
              ],</p>
            <p><span class="line-no">05</span>&nbsp;&nbsp;project: <span class="str">"{{ featuredProject?.title || 'Portfolio' }}"</span>,</p>
            <p><span class="line-no">06</span>&nbsp;&nbsp;status: <span class="fn">ready</span></p>
            <p><span class="line-no">07</span>&#125;</p>
          </div>
          <div class="console-footer">
            <span>build passed</span>
            <span>{{ currentExperience?.company || profile.location }}</span>
          </div>
        </aside>
      </template>
      <template v-else>
        <div class="banner-content loading-state">
          <div class="prompt-line"><span class="user">portfolio@dev</span>:~$&nbsp;<span class="cmd">loading</span></div>
          <h1 class="main-title">
            &gt; <span class="name-highlight">{{ error ? "Dados indisponíveis" : "Carregando..." }}</span><span class="cursor"></span>
          </h1>
          <p class="subtitle" v-if="error">
            <span class="str">Erro ao carregar {{ profileUrl }}: {{ error }}</span>
          </p>
        </div>
      </template>
    </div>
  </section>

  <main v-if="profile">
    <section id="sobre">
      <div class="section-inner">
        <div class="section-label">about</div>
        <h2 class="sec-title">Apresentação</h2>
        <div class="two-col">
          <div class="bio">
            <span class="comment">/**</span>
            <p>
              <span class="kw">export const</span> <span class="fn">developer</span> = () =&gt; &#123;<br />
              &nbsp;&nbsp;<span class="kw">return</span> &#123;<br />
              &nbsp;&nbsp;&nbsp;&nbsp;nome: <span class="str">"{{ profile.name }}"</span>,<br />
              &nbsp;&nbsp;&nbsp;&nbsp;formacao: <span class="str">"{{ profile.education[0]?.title || "" }}"</span>,<br />
              &nbsp;&nbsp;&nbsp;&nbsp;foco: [
              <template v-for="(item, index) in focus" :key="item">
                <span class="str">"{{ item }}"</span><span v-if="index < focus.length - 1">, </span>
              </template>
              ],<br />
              &nbsp;&nbsp;&nbsp;&nbsp;status: <span class="str">"{{ profile.portfolio.status }}"</span><br />
              &nbsp;&nbsp;&#125;<br />
              &#125;
            </p>
            <p class="bio-text">{{ profile.summary }}</p>
          </div>
          <div>
            <div class="profile-frame">
              <div class="profile-scan"></div>
              <div class="profile-initials">{{ profile.portfolio.profile_initials }}</div>
            </div>
            <div class="profile-label">{{ profile.portfolio.profile_label }}</div>
          </div>
        </div>
      </div>
    </section>

    <section id="stacks">
      <div class="section-inner">
        <div class="section-label">skills</div>
        <h2 class="sec-title">Stacks &amp; Habilidades</h2>
        <div class="stack-grid">
          <div class="stack-card" v-for="skill in skills" :key="skill.name">
            <div class="stack-icon" :class="skill.className">{{ skill.icon }}</div>
            <div class="stack-name">{{ skill.name }}</div>
            <div class="stack-tag">{{ skill.level }}</div>
          </div>
        </div>
      </div>
    </section>

    <section id="trajetoria">
      <div class="section-inner">
        <div class="section-label">career</div>
        <h2 class="sec-title">Trajetória</h2>
        <div class="timeline">
          <div class="tl-item active" v-for="item in timeline" :key="`${item.year}-${item.title}`">
            <div class="tl-year">{{ item.year }}</div>
            <div class="tl-title"><span class="tl-check">[✓]</span> {{ item.title }}</div>
            <div class="tl-desc">{{ item.desc }}</div>
          </div>
        </div>
      </div>
    </section>

    <section id="projetos">
      <div class="section-inner">
        <div class="section-label">work</div>
        <h2 class="sec-title">Projetos &amp; Entregas</h2>
        <div class="proj-grid">
          <div class="proj-card" v-for="project in profile.projects" :key="project.title">
            <div class="proj-header">
              <div class="file-icon" :class="project.icon_class">{{ project.icon }}</div>
              <div class="proj-name">{{ project.title }}</div>
              <div class="proj-arch">{{ project.type }}</div>
            </div>
            <p class="proj-desc">{{ project.description }}</p>
            <div class="proj-tags">
              <span class="tag" v-for="tag in project.tags" :key="tag">{{ tag }}</span>
            </div>
            <div class="proj-links">
              <a v-for="link in project.links" :key="link.url" :href="link.url" target="_blank" rel="noopener">{{ link.label }}</a>
            </div>
          </div>
        </div>
      </div>
    </section>

    <section id="contato">
      <div class="section-inner contact-center">
        <div class="section-label">contact</div>
        <h2 class="sec-title">Contatos</h2>
        <p class="contact-sub"><span class="accent2">&gt;</span> Disponível para oportunidades e colaborações.</p>
        <div class="contact-grid">
          <a v-for="contact in contacts" :key="contact.label" :href="contact.url" :target="contact.url.startsWith('mailto:') ? undefined : '_blank'" rel="noopener" class="contact-link">
            <span class="contact-icon">{{ contact.icon }}</span>
            <span>{{ contact.label }}</span>
          </a>
        </div>
      </div>
    </section>
  </main>

  <footer v-if="profile">
    <span class="footer-user">{{ terminalUser }}@dev</span>:~$
    <span class="footer-comment">// made with {{ profile.portfolio.footer_stack.join(" + ") }} + &lt;3</span>
    <div class="footer-copy">© {{ profile.portfolio.copyright_year }} {{ profile.name }}</div>
  </footer>
</template>
