# chronyd 4.8 (NTS)

This directory contains the definition for the `unikraft.org/chronyd:4.8-nts`
image, an NTP server running [chrony](https://chrony-project.org/) in binary
compatibility mode with [Network Time Security](https://datatracker.ietf.org/doc/html/rfc8915)
enabled.

Every upstream source in [conf/chrony.conf](conf/chrony.conf) is authenticated
with NTS. Clients of this server still get plain NTP: serving NTS would require
our own certificate, so this variant only authenticates upstream.

To run this image, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli)
and then you can run:

```console
kraft run -M 64M -p 1123:123/udp --plat qemu --arch x86_64 unikraft.org/chronyd:4.8-nts
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

The `/udp` suffix is required: `kraft` forwards TCP when no protocol is given,
and NTP queries then get no reply from an otherwise healthy server. Host port
123 needs root to bind, so the example uses a high port; serve real clients with
`-p 123:123/udp` as root.

Wait ~30 s after boot then query the server:

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
kraft run -M 64M -p 1123:123/udp --plat qemu .
```

## Notes

- Differs from [../4.8](../4.8/README.md) only in the crypto: chrony is built
  with gnutls (`+NTS`), so the rootfs also carries the gnutls dependency closure
  and the CA bundle used to validate NTS-KE certificates.
- NTS-KE needs outbound **TCP 4460** in addition to UDP 123.
- Certificate validation compares the certificate's validity window against the
  guest clock. On platforms that boot with a bogus clock every NTS-KE session
  fails with `certificate is not yet valid` where plain NTP would have worked;
  see the commented `nocerttimecheck` escape hatch in the configuration.

## See also

- [How to run unikernels locally in Unikraft's Documentation](https://unikraft.org/docs/cli/running).
- [chrony's documentation](https://chrony-project.org/documentation.html)
