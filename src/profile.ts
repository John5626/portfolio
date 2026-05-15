import type { Profile } from "./types";

export const profileUrl = "/data/profile.json";

export async function loadProfile(): Promise<Profile> {
  const response = await fetch(profileUrl);
  if (!response.ok) {
    throw new Error(`HTTP ${response.status}`);
  }
  return response.json();
}

export function toArray<T>(value: T[] | null | undefined): T[] {
  return Array.isArray(value) ? value : [];
}

export function uniqueSkills(profile: Profile): string[] {
  const seen = new Set<string>();
  const skills: string[] = [];

  toArray(profile.skills).forEach((group) => {
    toArray(group.items).forEach((item) => {
      const label = String(item).replace(/\s*\([^)]*\)/g, "").trim();
      const key = label.toLowerCase();
      if (!key || seen.has(key)) return;
      seen.add(key);
      skills.push(label);
    });
  });

  return skills;
}

export function firstName(profile: Profile): string {
  return String(profile.display_name || profile.name || "portfolio").split(" ")[0];
}
