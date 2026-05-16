# João Victor | Portfólio + Currículo ATS

Projeto em Vue 3 + TypeScript de portfólio web, um editor local e um currículo ATS em HTML/PDF.

## Fonte única

Edite pela interface:

```text
http://127.0.0.1:5500/admin.html
```

Ou diretamente no arquivo:

```text
data/profile.json
```

Esse arquivo alimenta:

- o portfólio Vue em `index.html`;
- o editor Vue em `admin.html`;
- o currículo ATS gerado em `dist/cv.html`;
- o PDF gerado em `dist/curriculo_JSOUZA.pdf`.

## Comandos

Instalar dependências:

```bash
npm install
```

Rodar portfólio + editor + API local:

```bash
npm run dev
```

Abrir:

```text
http://127.0.0.1:5500/
http://127.0.0.1:5500/admin.html
```

Validar TypeScript:

```bash
npm run typecheck
```

Gerar site Vue e HTML ATS para produção:

```bash
npm run build
```

O build de produção gera o portfólio público em `dist/site/` sem a página `admin.html` e sem o link `editar`.
Também copia para `dist/site/` os dados públicos em `data/profile.json`, o currículo HTML em `dist/cv.html` e o PDF público salvo em `public/dist/curriculo_JSOUZA.pdf`.
Esse comando não executa Chromium/Playwright, para funcionar em hospedagens estáticas.

Gerar ou atualizar o PDF localmente:

```bash
npm run pdf
```

Esse comando usa Playwright localmente, gera `dist/curriculo_JSOUZA.pdf` e sincroniza uma cópia versionável em `public/dist/curriculo_JSOUZA.pdf`, que é a cópia usada no deploy.
Em uma máquina nova, instale o Chromium local do Playwright antes de gerar o PDF:

```bash
npm run pdf:install
```

Gerar tudo localmente, incluindo PDF, em uma única chamada:

```bash
npm run build:with-pdf
```

No deploy estático, use `npm run build`. Se a plataforma ainda tentar baixar browsers do Playwright durante a instalação das dependências, configure a variável de ambiente `PLAYWRIGHT_SKIP_BROWSER_DOWNLOAD=1`; o build de produção não depende de Chromium.

## Estrutura atual

```text
curriculo/
├─ index.html
├─ admin.html
├─ src/
│  ├─ PortfolioApp.vue
│  ├─ AdminApp.vue
│  ├─ main.ts
│  ├─ admin.ts
│  ├─ profile.ts
│  └─ types.ts
├─ css/
│  ├─ style.css
│  └─ editor.css
├─ data/
│  └─ profile.json
├─ templates/
│  ├─ ats.html
│  └─ style.css
├─ scripts/
│  ├─ dev.mjs
│  ├─ dev-server.mjs
│  ├─ render.mjs
│  └─ export-pdf.mjs
├─ dist/
│  ├─ site/
│  ├─ cv.html
│  └─ curriculo_JSOUZA.pdf
├─ vite.config.ts
├─ tsconfig.json
├─ package.json
└─ package-lock.json
```

## Editor web

O editor é uma ferramenta local. Ao rodar `npm run dev`, o script habilita `EDITOR_ENABLED=true` e `VITE_ENABLE_EDITOR=true`, deixando a tela `/admin.html` disponível.

Em produção, a edição fica desabilitada por padrão:

- o link `editar` não é renderizado no portfólio;
- `admin.html` não entra em `dist/site/` no `npm run build`;
- a API local bloqueia `PUT /api/profile`, `POST /api/build` e `POST /api/pdf` quando `EDITOR_ENABLED` não está ativo.

Quando habilitado localmente, o editor salva em `data/profile.json` usando a API local do Node. Ele também consegue disparar:

- `Gerar HTML`: recria `dist/cv.html`;
- `Gerar PDF`: recria `dist/curriculo_JSOUZA.pdf` e atualiza `public/dist/curriculo_JSOUZA.pdf`.
