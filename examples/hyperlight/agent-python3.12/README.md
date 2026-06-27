# Python Productivity Agent Example on Hyperlight

This example runs a "productivity agent" Python environment loaded with multiple third-party libraries (Jinja2, BeautifulSoup, openpyxl, pypdf, tenacity, tqdm, click, python-dotenv, tabulate, markdown-it-py, pyyaml) executing `agent.py`.
Output reports are generated and written directly to the host using a HostFS volume mount.

## Requirements

- `kraft` installed on your path.
- `hyperlight-unikraft` VMM installed on your path.

## How to Build

1. Build the kernel:
   ```bash
   just build
   ```
   Or manually:
   ```bash
   kraft build --plat hyperlight --arch x86_64
   ```

2. Build the rootfs (initrd):
   ```bash
   just rootfs
   ```
   *Note: Alternatively, KraftKit allows you to pass a `Dockerfile` path directly to the `rootfs`/`initrd` configuration or command-line flag (e.g., `--initrd Dockerfile`), and it will build and package the rootfs on the fly.*

## How to Run

Run the agent script:
```bash
just run
```
Or manually:
```bash
kraft run --plat hyperlight --memory 1Gi --rootfs python-agent-initrd.cpio --hyperlight-mount ./work .unikraft/build/python-agent-hyperlight_hyperlight-x86_64 --as=kernel -- /agent.py
```
To run arbitrary Python code snippets without rebuilding:
```bash
just exec "import yaml; print(yaml.__version__)"
```
Or manually:
```bash
kraft run --plat hyperlight --memory 1Gi --rootfs python-agent-initrd.cpio --hyperlight-exec "import yaml; print(yaml.__version__)" .unikraft/build/python-agent-hyperlight_hyperlight-x86_64 --as=kernel
```
