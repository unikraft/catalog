# Catalog for Maintainers

These are common instructions for applications in the extended maintainers catalog.
Each application gets their own directory, used for documenting, setting up, configuring, building, running, testing and debugging the application.
Common information, configuration scripts are collected together in other directories such as `utils/`.

## Instructions for Bincompat Apps

The following are common information for examples of applications running in binary compatibility (i.e. **bincompat**) mode.
Instructions assume you are running commands in the application example subdirectory.

Applications running in binary compatibility mode use [`app-elfloader`](https://github.com/unikraft/app-elfloader) images to load and run native Linux ELFs (*Executable and Linking Format* files).
The images are generated using `library/base/`.
We call them `base` images or `base` kernels.

The images are also stored in the Unikraft registry and can be pulled from there.

### Directory Contents

A typical directory for a bincompat app contains:

* `Kraftfile`: build / run rules, including pulling the `base` image
* `Dockerfile`: filesystem, including binary and libraries
* `Makefile`: used to generate the root filesystem from the `Dockerfile` rules
* `README.md`: specific application instructions, such as starting and testing an application
* `config.yaml`: configuration file to generate script files to run the application
* specific application files, such as configuration files and source code files

### Common Setup

The following are required before building and running a bincompat app.
In case you have already done them for other bincompat runs, you can skip them:

1. [Install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli).

1. Configure `kraft` to be able to pull contents from GitHub.
   For this, first [generate a GitHub token](https://github.com/settings/tokens/new) that has all the `repo` list items checked.
   Configure `kraft` to use the token:

   ```console
   kraft login -u <username> -t <token> github.com
   ```

   In the command above, replace `<username>` with your GitHub username and `<token>` with the generated token.

1. Install Docker following the [official instructions](https://docs.docker.com/engine/install/).
   This can be either [Docker Engine](https://docs.docker.com/engine/) or [Docker Desktop](https://docs.docker.com/desktop/).

1. Start a [BuildKit](https://docs.docker.com/build/buildkit/) container to be used by KraftKit to build the filesystem from the Dockerfile.
   Source the corresponding script from the `utils/` directory.
   This can be one of the following commands, depending on the location of your application directory:

   ```console
   source ../../utils/start-buildkit.sh
   source ../../../utils/start-buildkit.sh
   ```

1. Running the application requires kernel images (called `base` kernel images).
   If not already generated, generate the kernels in the `kernels/` directory, while inside the `library/base/` directory:
   This can be one of the following commands, depending on the location of your application directory:

   ```console
   ../../utils/bincompat/base-build-all.sh
   ../../../utils/bincompat/base-build-all.sh
   ```

## Specific Setup

`config.yaml` is used to generate the scripts and configuration files required to build and run the application.
To generate these files, run one of the following commands, depending on the location of your application directory:

```console
../../utils/bincompat/generate.py
```

It generates the `run*` scripts and configuration files used to run the application in bincompat mode using different tools / VMMs.

### Build, Run and Use

You build and run the application using [KraftKit](https://github.com/unikraft/kraftkit).
Follow the specific instructions in the `README.md` file in the application directory for specifics on building and running with KraftKit and on using the application.

### Scripted Run

To make it easier to run application in bincompat mode, use the generated scripts.
Follow the steps:

1. Build the application root filesystem as an initial ramdisk from the `Dockerfile` using:

   ```console
   make initrd
   ```

   This creates the `rootfs/` directory and the `rootfs.cpio` file with the root filesystem:

   ```console
   tree rootfs/
   ```

1. Run the scripts:

   ```console
   ./run-qemu-x86_64.sh
   ./run-fc-x86_64.sh
   ./kraft-run-qemu.sh
   ```

   All scripts start a local instance of the `base` image with the application running in bincompat mode.
   The application filesystem (binary executable, libraries, configuration files) are packed inside the `rootfs.cpio` initrd file.
   There is no Kraft script to run Firecracker, as Kraft doesn't currently support running images with networking support using Firecracker.

1. You can run the `strace` or `debug` kernels with the scripts:

   ```console
   ./run-qemu-x86_64.sh ../../kernels/base_qemu-x86_64-strace
   ./run-qemu-x86_64.sh ../../kernels/base_qemu-x86_64-debug
   ```

1. Build, run and use the application as detailed in the application `README.md`.
