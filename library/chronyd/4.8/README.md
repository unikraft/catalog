# chronyd 4.8

This directory contains the definition for the `unikraft.org/chronyd:4.8` image,
an NTP server running [chrony](https://chrony-project.org/) in binary
compatibility mode.

To run this image, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli)
and then you can run:

```console
kraft run -M 16M -p 1123:123/udp --plat qemu --arch x86_64 unikraft.org/chronyd:4.8
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

The `/udp` suffix is required: `kraft` forwards TCP when no protocol is given,
and NTP queries then get no reply from an otherwise healthy server. Host port
123 needs root to bind, so the example uses a high port; serve real clients with
`-p 123:123/udp` as root.

Wait ~20 s after boot for the upstream sync (iburst), then query the server:

```console
python3 test.py
```

It reports the stratum, the reference ID of the selected upstream and the served
time, exiting non-zero until chronyd has synchronized.

## Building from source

To build the image locally, clone this repository and `cd` into this directory.
Then run:

```console
kraft build --plat qemu --arch x86_64 .
```

To run the locally built image, use `.` (_dot_, the current directory) as the
final argument:

```console
kraft run -M 16M -p 1123:123/udp --plat qemu .
```

## Notes

- chrony is compiled from source with `HAVE_RECVMMSG` removed from `config.h`.
  Unikraft has no `recvmmsg` syscall and the stock Alpine binary has no runtime
  fallback, so it busy-loops on a socket it can never drain.
- The configuration is baked in at build time from
  [conf/chrony.conf](conf/chrony.conf); a unikernel has no shell to generate one
  at startup. Edit it and rebuild to change servers.
- chronyd runs with `-x`, so it never adjusts the guest clock, whose set/adjust
  syscalls are stubs on Unikraft. It still serves corrected time to clients.
- [conf/chrony.conf](conf/chrony.conf) sets `allow all`, so the instance answers
  any client that can reach the port. Narrow it (`allow 192.168.0.0/16`) before
  exposing it to an untrusted network.

## See also

- [How to run unikernels locally in Unikraft's Documentation](https://unikraft.org/docs/cli/running).
- [chrony's documentation](https://chrony-project.org/documentation.html)
