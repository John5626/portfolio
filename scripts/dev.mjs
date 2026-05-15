import { spawn } from "node:child_process";

const viteCommand = process.platform === "win32" ? "node_modules\\.bin\\vite.cmd" : "node_modules/.bin/vite";
const editorEnv = {
  ...process.env,
  EDITOR_ENABLED: "true",
  VITE_ENABLE_EDITOR: "true",
};

const processes = [
  spawn(process.execPath, ["scripts/dev-server.mjs", "5510"], {
    stdio: "inherit",
    env: editorEnv,
    shell: false,
  }),
  spawn(viteCommand, ["--host", "127.0.0.1", "--port", "5500"], {
    stdio: "inherit",
    env: editorEnv,
    shell: process.platform === "win32",
  }),
];

function stopAll(signal) {
  processes.forEach((child) => {
    if (!child.killed) child.kill(signal);
  });
}

process.on("SIGINT", () => {
  stopAll("SIGINT");
});

process.on("SIGTERM", () => {
  stopAll("SIGTERM");
});

processes.forEach((child) => {
  child.on("exit", (code) => {
    if (code && code !== 0) {
      stopAll("SIGTERM");
      process.exitCode = code;
    }
  });
});
