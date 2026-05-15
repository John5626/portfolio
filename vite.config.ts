import { defineConfig, loadEnv } from "vite";
import vue from "@vitejs/plugin-vue";
import { resolve } from "node:path";
import { fileURLToPath } from "node:url";

const root = fileURLToPath(new URL(".", import.meta.url));

export default defineConfig(({ command, mode }) => {
  const env = loadEnv(mode, root, "");
  const editorEnabled = command === "serve" || env.VITE_ENABLE_EDITOR === "true";
  const input: Record<string, string> = {
    main: resolve(root, "index.html"),
  };

  if (editorEnabled) {
    input.admin = resolve(root, "admin.html");
  }

  return {
    plugins: [vue()],
    server: {
      host: "127.0.0.1",
      port: 5500,
      proxy: {
        "/api": "http://127.0.0.1:5510",
      },
    },
    build: {
      outDir: "dist/site",
      emptyOutDir: true,
      rollupOptions: {
        input,
      },
    },
  };
});
