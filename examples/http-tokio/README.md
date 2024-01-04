Build command:

```console
KRAFTKIT_TARGET=http-tokio cargo +nightly build --target x86_64-unikraft-linux-musl -Z build-std=std,panic_abort
```

To run just do:
```console
sudo kraft run
```