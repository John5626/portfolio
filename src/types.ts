export type SkillGroup = {
  group: string;
  items: string[];
};

export type Experience = {
  role: string;
  company: string;
  date: string;
  location?: string;
  bullets: string[];
};

export type Education = {
  title: string;
  subtitle: string;
  date: string;
};

export type Language = {
  name: string;
  note: string;
  level?: string;
};

export type ProjectLink = {
  label: string;
  url: string;
};

export type Project = {
  title: string;
  type: string;
  stack: string;
  description: string;
  tags: string[];
  icon: string;
  icon_class: string;
  links: ProjectLink[];
};

export type PortfolioSettings = {
  terminal_user: string;
  logo_name: string;
  command: string;
  focus: string[];
  status: string;
  profile_initials: string;
  profile_label: string;
  profile_image_path?: string;
  profile_image_alt?: string;
  skill_levels: Record<string, string>;
  resume_pdf_path: string;
  resume_html_path: string;
  resume_download_name: string;
  resume_output_pdf: string;
  copyright_year: string;
  footer_stack: string[];
};

export type Profile = {
  name: string;
  display_name: string;
  title: string;
  short_title: string;
  email: string;
  phone_e164: string;
  phone_display: string;
  location: string;
  linkedin_text: string;
  linkedin_url: string;
  github_text: string;
  github_url: string;
  website_text: string;
  website_url: string;
  summary: string;
  skills: SkillGroup[];
  experience: Experience[];
  education: Education[];
  languages: Language[];
  projects: Project[];
  portfolio: PortfolioSettings;
};
