# A "productivity agent" Python environment: the trimmed python-base
# + a dependency stack covering config, templating, data tables,
# HTML/Markdown, PDF, Excel, CLI wiring, retry/progress, and now
# numpy/pandas on top. numpy + pandas pull manylinux wheels with
# native cores; the trimmed base keeps libgcc_s / libstdc++ / librt /
# libpthread / libdl / libffi / libz around so those wheels load
# cleanly against the base's glibc ABI.

# BASE is resolved pre-FROM so the classic (non-BuildKit) docker
# frontend used by DOCKER_BUILDKIT=0 handles the substitution.
ARG BASE=ghcr.io/hyperlight-dev/hyperlight-unikraft/python-base:latest

# Stage 1: resolve + install pip deps into a target dir, then trim
# everything the guest doesn't need (pip/setuptools/wheel metadata,
# *.dist-info, test suites, __pycache__). .sos stay unstripped here
# because several already ship stripped and the numpy/pandas ones
# are the bulk of the size anyway.
FROM python:3.12-slim AS deps
RUN pip install --target=/deps --no-cache-dir \
    tqdm \
    pyyaml \
    jinja2 \
    beautifulsoup4 \
    tabulate \
    click \
    tenacity \
    python-dotenv \
    pypdf \
    openpyxl \
    markdown-it-py \
    pydantic \
    pillow \
    lxml \
    cryptography \
    python-dateutil \
    numpy \
    pandas
RUN set -eux; \
    # Drop .dist-info metadata — not needed at runtime.
    find /deps -maxdepth 1 -type d -name '*.dist-info' -exec rm -rf {} + 2>/dev/null || true; \
    # Drop test suites shipped inside packages.
    find /deps \( -type d -name tests -o -type d -name test \) -exec rm -rf {} + 2>/dev/null || true; \
    # Drop pycache + pyc.
    find /deps -type d -name __pycache__ -exec rm -rf {} + 2>/dev/null || true; \
    find /deps -type f -name '*.pyc' -delete 2>/dev/null || true; \
    # Strip .sos shipped by wheels (numpy/pandas/pillow/lxml/cryptography).
    find /deps -name '*.so*' -exec strip --strip-unneeded {} + 2>/dev/null || true

# No subprocess-ready binaries yet — the kernel's vfork+execve works,
# but app-elfloader crashes the child on stack setup (page fault at
# low addresses during any exec, even Python → Python). Tracked as
# follow-up work. For now the agent runs as a single process.

# Stage 2: layer deps onto python-base.
FROM ${BASE} AS rootfs
COPY --from=deps /deps /usr/local/lib/python3.12/site-packages
COPY agent.py /agent.py

# Stage 3: pack as CPIO.
FROM alpine:3.20 AS cpio
RUN apk add --no-cache cpio findutils
COPY --from=rootfs / /rootfs/
RUN cd /rootfs && find . | cpio -o -H newc > /output.cpio 2>/dev/null
