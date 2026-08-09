# Mosquitto 2.0.21 Image

This directory contains the definition for the `unikraft.org/mosquitto:2.0.21` image running the Eclipse Mosquitto MQTT broker.

## Prerequisites

- Install Unikraft’s CLI toolchain:  
    ```console
    curl -sSL https://unikraft.org/install | console
    ```
- On the host, install Mosquitto clients (`mosquitto-clients` package) to run `mosquitto_sub` / `mosquitto_pub`.

## Build and Run

1. **Build the unikernel** (from this directory):
    ```console
    kraft build --no-cache --plat qemu --arch x86_64 .
    ```
2. **Run the unikernel** (as root):
    ```console
    kraft run \
        -M 1024M \
        -p 1883:1883 .
    ```

   By default this will listen for MQTT on port `1883`.

## Connecting from the Host

With the unikernel running, open a second terminal on your host and:

- **Subscribe** to topic `test/topic`:

  ```console
  mosquitto_sub -h localhost -t 'test/topic' -v
  ```
- **Publish** a message:

  ```console
  mosquitto_pub -h localhost -t 'test/topic' -m 'Hello from Unikraft!'
  ```

You should see your “Hello…” payload appear in the subscriber terminal.

## mosquitto.conf Active Settings

Below are the **uncommented** lines in [`mosquitto.conf`](mosquitto.conf) (all other options remain at their defaults):

| Setting           | Value          | Description                                                  |
| ----------------- | -------------- | ------------------------------------------------------------ |
| `user`            | `root`         | Run the broker as the `root` user (default if unset).        |
| `listener`        | `1883 0.0.0.0` | Listen on TCP port **1883** on **all** interfaces (0.0.0.0). |
| `allow_anonymous` | `true`         | Allow clients to connect without a username / password.        |

Any additional configuration parameters can be enabled by uncommenting and adjusting their values in [`mosquitto.conf`](mosquitto.conf).

## See also

- [Unikraft CLI: Running Unikernels Locally](https://unikraft.org/docs/cli/running)
- [Mosquitto Configuration Reference (`mosquitto.conf(5)`)](https://mosquitto.org/man/mosquitto-conf-5.html)
