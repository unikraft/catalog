# Unikraft - MTR port

This folder contains the port of MTR (My Traceroute) for Unikraft.
MTR is a network diagnostic tool that combines the functionality of the `traceroute` and `ping` programs.

> [!CAUTION]
> PROGRAM DOES NOT WORK!! `fork()` is not implemented in Unikraft as of writing,
> which `mtr` depends on. Prepare to be disappointed :-)
