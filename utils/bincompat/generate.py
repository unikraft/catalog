#!/usr/bin/env python

# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2023, Unikraft GmbH and The Unikraft Authors.

"""Generate run scripts for Unikraft bincompat applications.

Use QEMU, Firecracker and Krafkit for running.
"""

import sys
import os
import stat
import yaml


TEMPLATE_RUN_QEMU_HEADER = """#!/bin/sh

kernel="{}"
cmd="{}"

if test $# -eq 1; then
    kernel="$1"
fi
"""

RUN_COMMON_NET_COMMANDS = """
# Remove previously created network interfaces.
sudo ip link set dev tap0 down 2> /dev/null
sudo ip link del dev tap0 2> /dev/null
sudo ip link set dev virbr0 down 2> /dev/null
sudo ip link del dev virbr0 2> /dev/null
"""

RUN_QEMU_NET_COMMANDS = """
# Create bridge interface for QEMU networking.
sudo ip link add dev virbr0 type bridge
sudo ip address add 172.44.0.1/24 dev virbr0
sudo ip link set dev virbr0 up
"""

RUN_FIRECRACKER_NET_COMMANDS = """
# Create tap interface for Firecracker networking.
sudo ip tuntap add dev tap0 mode tap
sudo ip address add 172.44.0.1/24 dev tap0
sudo ip link set dev tap0 up
"""

RUN_KRAFT_NET_COMMANDS = """
# Create bridge interface for KraftKit networking.
sudo kraft net create -n 172.44.0.1/24 virbr0
"""

TEMPLATE_RUN_FIRECRACKER_HEADER = """#!/bin/sh

config="{}"

if test $# -eq 1; then
    config="$1"
fi
"""

RUN_FIRECRACKER_PRE_TRAILER = """
# Remove previously created files.
sudo rm -f /tmp/firecracker.log
touch /tmp/firecracker.log
sudo rm -f /tmp/firecracker.socket
"""

RUN_FIRECRACKER_COMMAND = """firecracker-x86_64 \\
        --api-sock /tmp/firecracker.socket \\
        --config-file "$config"
"""

RUN_KRAFT_HEADER = """#!/bin/sh
"""

RUN_KILL_COMMANDS = """
# Clean up any previous instances.
sudo pkill -f qemu-system 2> /dev/null
sudo pkill -f firecracker 2> /dev/null
sudo kraft stop --all 2> /dev/null
sudo kraft rm --all 2> /dev/null
"""

CONFIG = "config.yaml"
KRAFTCONFIG = "Kraftfile"


def files(path):
    """Extract regular files in given directory.

    Ignore directories or other file types.
    """

    for file in os.listdir(path):
        if os.path.isfile(os.path.join(path, file)):
            yield file


def generate_run_fc_json(config, kernel):
    """Generate running config (JSON) for Firecracker."""

    kernel_path = os.path.join(config["kerneldir"], kernel)
    suffix = kernel.replace("base_", "")

    json_name = os.path.join(config["rundir"], f"{suffix}.json")
    with open(json_name, "w", encoding="utf8") as stream:
        stream.write("{\n")
        stream.write('  "boot-source": {\n')
        stream.write(f'    "kernel_image_path": "{kernel_path}",\n')
        stream.write(f'    "boot_args": "{kernel} ')
        if config["networking"]:
            stream.write("netdev.ipv4_addr=172.44.0.2 netdev.ipv4_gw_addr=172.44.0.1 ")
            stream.write("netdev.ipv4_subnet_mask=255.255.255.0 ")
        stream.write('vfs.fstab=[ \\"initrd:/:initrd:::\\" ] ')
        stream.write(f"-- {config['cmd']}\"")
        stream.write(',\n    "initrd_path": "rootfs.cpio"')
        stream.write("\n  },\n")
        stream.write(
            f"""  "drives": [],
  "machine-config": {{
    "vcpu_count": 1,
    "mem_size_mib": {config['memory']},
    "smt": false,
    "track_dirty_pages": false
  }},
  "cpu-config": null,
  "balloon": null,
"""
        )
        if config["networking"]:
            stream.write(
                """  "network-interfaces": [
    {
      "iface_id": "net1",
      "guest_mac":  "06:00:ac:10:00:02",
      "host_dev_name": "tap0"
    }
  ],
"""
            )
        stream.write(
            """  "vsock": null,
  "logger": {
    "log_path": "/tmp/firecracker.log",
    "level": "Debug",
    "show_level": true,
    "show_log_origin": true
  },
  "metrics": null,
  "mmds-config": null,
  "entropy": null
}
"""
        )


def generate_run_fc(config):
    """Generate running script using Firecracker."""
    header = TEMPLATE_RUN_FIRECRACKER_HEADER.format(f"fc-{config['arch']}.json")

    out_file = os.path.join(config["rundir"], f"run-fc-{config['arch']}.sh")
    with open(out_file, "w", encoding="utf8") as stream:
        stream.write(header)
        stream.write(RUN_KILL_COMMANDS)
        if config["networking"]:
            stream.write(RUN_COMMON_NET_COMMANDS)
            stream.write(RUN_FIRECRACKER_NET_COMMANDS)
        stream.write(RUN_FIRECRACKER_PRE_TRAILER)
        if config["networking"]:
            stream.write("sudo ")
        stream.write(RUN_FIRECRACKER_COMMAND)
        stbuf = os.stat(out_file)
        os.chmod(out_file, stbuf.st_mode | stat.S_IEXEC)


def generate_run_qemu(config, kernel):
    """Generate running script using QEMU."""

    kernel_path = os.path.join(config["kerneldir"], kernel)
    suffix = kernel.replace("base_", "")
    header = TEMPLATE_RUN_QEMU_HEADER.format(kernel_path, config["cmd"])

    out_file = os.path.join(config["rundir"], f"run-{suffix}.sh")
    with open(out_file, "w", encoding="utf8") as stream:
        stream.write(header)
        stream.write(RUN_KILL_COMMANDS)
        if config["networking"]:
            stream.write(RUN_COMMON_NET_COMMANDS)
            stream.write(RUN_QEMU_NET_COMMANDS)
        stream.write("\n")
        if config["networking"]:
            stream.write("sudo ")
        if config["arch"] == "x86_64":
            stream.write("qemu-system-x86_64 \\\n")
            if "accel" in config.keys():
                if config["accel"]:
                    stream.write("    -accel kvm \\\n")
        else:
            stream.write("qemu-system-aarch64 \\\n")
            stream.write("    -machine virt \\\n")
        stream.write('    -kernel "$kernel" \\\n')
        stream.write("    -nographic \\\n")
        stream.write(f"    -m {config['memory']}M \\\n")
        if config["networking"]:
            stream.write("    -netdev bridge,id=en0,br=virbr0 ")
            stream.write("-device virtio-net-pci,netdev=en0 \\\n")
            stream.write('    -append "netdev.ipv4_addr=172.44.0.2 ')
            stream.write("netdev.ipv4_gw_addr=172.44.0.1 ")
            stream.write("netdev.ipv4_subnet_mask=255.255.255.0 ")
            stream.write('vfs.fstab=[ \\"initrd:/:initrd:::\\" ] ')
            stream.write('-- $cmd" \\\n')
        else:
            stream.write('    -append "')
            stream.write('vfs.fstab=[ \\"initrd:/:initrd:::\\" ] ')
            stream.write('-- $cmd" \\\n')
        stream.write('    -initrd "$PWD"/rootfs.cpio \\\n')
        stream.write("    -cpu max\n")
        stbuf = os.stat(out_file)
        os.chmod(out_file, stbuf.st_mode | stat.S_IEXEC)


def generate_run_kraft(config, plat):
    """Generate running script using KraftKit."""

    out_file = os.path.join(config["rundir"], f"kraft-run-{plat}.sh")
    with open(out_file, "w", encoding="utf8") as stream:
        stream.write(RUN_KRAFT_HEADER)
        stream.write(RUN_KILL_COMMANDS)
        if config["networking"]:
            stream.write(RUN_COMMON_NET_COMMANDS)
            stream.write(RUN_KRAFT_NET_COMMANDS)
        stream.write("\n")
        if config["networking"]:
            stream.write("sudo ")
        stream.write(
            "KRAFTKIT_BUILDKIT_HOST=docker-container://buildkitd kraft run \\\n"
        )
        if "accel" not in config.keys():
            stream.write("    -W \\\n")
        elif not config["accel"]:
            stream.write("    -W \\\n")
        if config["arch"]:
            stream.write("    -W \\\n")
        stream.write(f"    --memory {config['memory']}M \\\n")
        stream.write("    --log-level debug --log-type basic \\\n")
        if config["networking"]:
            stream.write("    --network bridge:virbr0 \\\n")
        stream.write(f"    --arch {config['arch']} --plat {plat}\n")

        stbuf = os.stat(out_file)
        os.chmod(out_file, stbuf.st_mode | stat.S_IEXEC)


def generate_run(config):
    """Generate running scripts."""

    generate_run_fc_json(config, "base_fc-x86_64")
    generate_run_fc_json(config, "base_fc-x86_64-strace")
    generate_run_fc_json(config, "base_fc-x86_64-debug")
    generate_run_fc(config)
    generate_run_qemu(config, "base_qemu-x86_64")
    generate_run_kraft(config, "qemu")


def main():
    """The main program function calls generate functions."""

    # Obtain configurations for running applications.
    try:
        with open(CONFIG, "r", encoding="utf8") as stream:
            config = yaml.safe_load(stream)
    except IOError:
        print(f"Error: Unable to open configuration file '{CONFIG}'", file=sys.stderr)
        sys.exit(1)

    if not "rootfs" in config.keys():
        config["rootfs"] = "rootfs"
    if not "rundir" in config.keys():
        config["rundir"] = "."
    if not "kerneldir" in config.keys():
        config["kerneldir"] = "../../kernels"

    # Test if directories are available.
    try:
        with os.scandir(config["kerneldir"]) as _:
            pass
    except IOError:
        print(f"Error: Unable to access kernel directory '{config['kerneldir']}'", file=sys.stderr)
        sys.exit(1)

    try:
        with os.scandir(config["rundir"]) as _:
            pass
    except IOError:
        print(f"Error: Unable to access running directory '{config['rundir']}'", file=sys.stderr)

    # Currently only x86_64 is supported.
    config["arch"] = "x86_64"

    # Obtain targets for KraftKit runs form kraft.yaml.
    try:
        with open(KRAFTCONFIG, "r", encoding="utf8") as stream:
            data = yaml.safe_load(stream)
    except IOError:
        print(f"Error: Unable to open Kraft configuration file '{KRAFTCONFIG}'", file=sys.stderr)
        sys.exit(1)

    if not "name" in data.keys():
        print(f"Error: 'name' attribute is not defined in '{KRAFTCONFIG}'", file=sys.stderr)
        sys.exit(1)
    config["name"] = data["name"]

    if not "cmd" in data.keys():
        print(f"Error: 'cmd' attribute is not defined in '{KRAFTCONFIG}'", file=sys.stderr)
        sys.exit(1)
    config["cmd"] = " ".join(c for c in data["cmd"])

    generate_run(config)


if __name__ == "__main__":
    sys.exit(main())
