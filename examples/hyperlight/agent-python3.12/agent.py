#!/usr/bin/env python3
"""
A tiny "productivity agent" flow that exercises the pure-Python stack
bundled in this example's initrd.

It reads a YAML config from /host/config.yaml (falling back to an inline
default if /host isn't mounted), loops over the items with a tqdm progress
bar, renders a Markdown report with Jinja2, parses a scraped HTML snippet
with BeautifulSoup, demonstrates a tenacity retry, loads env vars with
python-dotenv, pretty-prints a table with tabulate, validates the config
shape, and writes three artifacts back to /host/:

    report.md
    report.xlsx
    report.pdf

If /host isn't mounted the artifacts are skipped but every library is
still exercised.
"""
import os
import zipfile

# Unikraft's ramfs reports epoch-0 (1970) for file mtimes. Python's
# zipfile rejects timestamps before 1980, which breaks openpyxl's
# XLSX writer (XLSX is a ZIP container). Clamp pre-1980 dates.
_orig_zi_init = zipfile.ZipInfo.__init__
def _safe_zi_init(self, filename="NoName", date_time=(1980, 1, 1, 0, 0, 0)):
    if date_time[0] < 1980:
        date_time = (1980, 1, 1, 0, 0, 0)
    _orig_zi_init(self, filename, date_time)
zipfile.ZipInfo.__init__ = _safe_zi_init

# 1. YAML config — either from /host or the inline fallback.
import yaml

DEFAULT_CONFIG = """\
project: Hyperlight productivity demo
owner: you
items:
  - {name: alpha, score: 95, tag: ok}
  - {name: beta,  score: 72, tag: review}
  - {name: gamma, score: 88, tag: ok}
  - {name: delta, score: 41, tag: fail}
"""

CONFIG_PATH = "/host/config.yaml"
cfg_text = (
    open(CONFIG_PATH).read() if os.path.exists(CONFIG_PATH) else DEFAULT_CONFIG
)
cfg = yaml.safe_load(cfg_text)
print(f"[yaml] loaded {len(cfg['items'])} items from "
      f"{'/host/config.yaml' if os.path.exists(CONFIG_PATH) else '<inline default>'}")


# 2. Schema check — keep it dependency-free; pydantic v2 pulls a Rust
#    wheel that the current python-base can't load. A single loop is
#    enough for this demo.
def validate(cfg):
    assert isinstance(cfg.get("project"), str), "project must be a string"
    assert isinstance(cfg.get("items"), list), "items must be a list"
    for it in cfg["items"]:
        assert {"name", "score", "tag"} <= it.keys(), f"bad item: {it}"
        assert isinstance(it["score"], int)
    return cfg


validate(cfg)
print(f"[validate] config for {cfg['project']!r} OK")


# 3. Progress bar over the items.
from tqdm import tqdm

processed = []
for item in tqdm(cfg["items"], desc="scoring", ncols=60):
    processed.append({**item, "pass": item["score"] >= 70})


# 4. BeautifulSoup — parse a scraped HTML blob.
from bs4 import BeautifulSoup

HTML = "<div class='notes'><h1>Run notes</h1><p>2026-04-18: auto-generated.</p></div>"
soup = BeautifulSoup(HTML, "html.parser")
notes = f"{soup.h1.text}: {soup.p.text}"
print(f"[bs4] extracted notes: {notes!r}")


# 5. python-dotenv — pull env from /host/.env if present.
from dotenv import dotenv_values

env_path = "/host/.env"
env = dict(os.environ)
if os.path.exists(env_path):
    env.update(dotenv_values(env_path))
    print(f"[dotenv] merged {env_path}")
env.setdefault("AGENT_RUN_ID", "demo-run-0001")
print(f"[dotenv] AGENT_RUN_ID={env['AGENT_RUN_ID']}")


# 6. tabulate — pretty terminal table.
from tabulate import tabulate

print("\n[tabulate]")
print(
    tabulate(
        [(p["name"], p["score"], p["tag"], "PASS" if p["pass"] else "FAIL")
         for p in processed],
        headers=["name", "score", "tag", "result"],
        tablefmt="github",
    )
)


# 7. tenacity — prove the retry decorator works with a flaky function.
from tenacity import retry, stop_after_attempt

attempts = 0

@retry(stop=stop_after_attempt(4), reraise=True)
def sometimes_fails():
    global attempts
    attempts += 1
    if attempts < 3:
        raise RuntimeError(f"nope, attempt {attempts}")
    return "got through"

print(f"\n[tenacity] {sometimes_fails()} after {attempts} attempts")


# 8. click — build a CLI in-process just to show it's wired up.
import click

@click.command()
@click.option("--greeting", default="hello")
@click.argument("who", default="agent")
def _greet(greeting, who):
    print(f"[click] {greeting}, {who}!")

_greet(standalone_mode=False, args=["--greeting", "hi", "world"])


# 9. Jinja2 — render a Markdown report.
from jinja2 import Template

MD_TEMPLATE = Template("""\
# {{ cfg.project }}

_Run ID: {{ env.AGENT_RUN_ID }}_

{{ notes }}

## Items

| name | score | tag | result |
|---|---:|---|---|
{%- for p in processed %}
| {{ p.name }} | {{ p.score }} | {{ p.tag }} | {{ "PASS" if p.pass else "FAIL" }} |
{%- endfor %}

- Pass rate: **{{ pass_rate }}%**
""")

pass_rate = round(sum(p["pass"] for p in processed) / len(processed) * 100)
md = MD_TEMPLATE.render(cfg=cfg, env=env, notes=notes,
                         processed=processed, pass_rate=pass_rate)


# 10. markdown-it-py — render the Markdown to HTML as a sanity check.
from markdown_it import MarkdownIt

html = MarkdownIt().render(md)
print(f"\n[markdown-it] rendered {len(md)} chars of markdown -> {len(html)} chars of HTML")


# 11. openpyxl — write an Excel workbook.
from openpyxl import Workbook

wb = Workbook()
ws = wb.active
ws.title = "scores"
ws.append(["name", "score", "tag", "pass"])
for p in processed:
    ws.append([p["name"], p["score"], p["tag"], p["pass"]])


# 12. pypdf — write a stub PDF with metadata. pypdf alone can't
#     synthesise a PDF from scratch; we just take a minimal
#     hand-written one, open/read/modify metadata, and save.
from pypdf import PdfWriter

writer = PdfWriter()
writer.add_blank_page(width=612, height=792)
writer.add_metadata({
    "/Title": cfg["project"],
    "/Producer": "hyperlight-unikraft python-agent demo",
    "/AgentRunID": env["AGENT_RUN_ID"],
})


# 13. Write artifacts out via the host mount (if available).
OUT = "/host"
if os.path.isdir(OUT):
    with open(f"{OUT}/report.md", "w") as f:
        f.write(md)
    wb.save(f"{OUT}/report.xlsx")
    with open(f"{OUT}/report.pdf", "wb") as f:
        writer.write(f)
    with open(f"{OUT}/report.html", "w") as f:
        f.write(html)
    print(f"\n[artifacts] wrote {OUT}/report.{{md,html,xlsx,pdf}}")
else:
    print("\n[artifacts] /host not mounted — skipping file output "
          "(run with --mount ./work to capture reports)")

print("\ndone.")
