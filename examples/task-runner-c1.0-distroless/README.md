# Task Runner

A minimal task runner written in C and packaged as a static distroless executable for Unikraft.

The example demonstrates a small concurrent task queue implemented with POSIX threads, mutex synchronization, and a fixed set of predefined tasks.

## Overview

The application creates two worker threads and executes three predefined tasks:

* `ADD(10, 32)`
* `FIB(10)`
* `SQUARE(7)`

Tasks are stored in a shared queue and workers take available tasks from the queue. Access to the queue is protected by a POSIX mutex.

The application requires no external input, files, network access, or configuration.

## Features

* Written in C
* Uses POSIX threads (`pthread`)
* Two concurrent worker threads
* Shared task queue
* Mutex-based synchronization
* Three simple task types
* Static compilation
* Position-independent executable (PIE)
* Distroless runtime image
* Runs as a Unikraft unikernel
* No external runtime dependencies

## Project Structure

```text
task-runner-c1.0-distroless/
├── Dockerfile
├── Kraftfile
├── README.md
└── src/
    └── main.c
```

## How It Works

At startup, the application creates a small queue containing three tasks.

```text
                ┌──────────────┐
                │  Task Queue  │
                └──────┬───────┘
                       │
              ┌────────┴────────┐
              │                 │
        ┌─────▼─────┐     ┌─────▼─────┐
        │  Worker 1 │     │  Worker 2 │
        └─────┬─────┘     └─────┬─────┘
              │                 │
              └────────┬────────┘
                       │
                 Execute Tasks
```

Each worker:

1. Acquires the queue mutex.
2. Checks whether a task is available.
3. Removes the next task from the queue.
4. Releases the mutex.
5. Executes the task.
6. Repeats until all tasks have been processed.

The mutex ensures that two workers cannot take the same task simultaneously.

## Tasks

### ADD

Adds two integer values.

```text
ADD(10, 32) = 42
```

### FIB

Calculates a Fibonacci number recursively.

```text
FIB(10) = 55
```

### SQUARE

Calculates the square of an integer.

```text
SQUARE(7) = 49
```

## Build with Docker

The Dockerfile uses a multi-stage build.

The first stage uses Alpine Linux with GCC and builds the application as a static position-independent executable.

The final stage uses:

```text
gcr.io/distroless/static-debian12
```

Only the compiled executable is copied into the final image.

Build the image with:

```bash
docker build -t task-runner .
```

## Run with Docker

Run the container with:

```bash
docker run --rm task-runner
```

Expected output:

```text
Task Runner
===========

[worker-1] ADD(10, 32) = 42
[worker-2] FIB(10) = 55
[worker-1] SQUARE(7) = 49

Completed: 3 tasks
```

The exact worker assigned to each task and the output order may vary because the tasks are executed concurrently.

## Build with Unikraft

Build the unikernel using KraftKit:

```bash
kraft build --plat qemu --arch x86_64 .
```

The Dockerfile is used as the root filesystem definition and the resulting executable is packaged into the Unikraft image.

## Run with Unikraft

Run the application with QEMU:

```bash
kraft run --rm -M 128M
```

Expected output:

```text
Task Runner
===========

[worker-1] ADD(10, 32) = 42
[worker-1] FIB(10) = 55
[worker-1] SQUARE(7) = 49

Completed: 3 tasks
```

The worker assignment and output order are not guaranteed because the workers execute concurrently.

## Dockerfile

The application is compiled as a static position-independent executable:

```dockerfile
RUN gcc \
    -O2 \
    -fPIE \
    -static-pie \
    -pthread \
    -o /task-runner \
    main.c
```

The position-independent executable is required for the Unikraft application ELF loader.

The final runtime image contains only the executable:

```dockerfile
FROM gcr.io/distroless/static-debian12

COPY --from=builder /task-runner /usr/bin/task-runner

ENTRYPOINT ["/usr/bin/task-runner"]
```

## Kraftfile

The example uses the Unikraft `base` runtime and the Dockerfile as its root filesystem:

```yaml
spec: v0.6

name: task-runner

runtime: base:latest

rootfs: ./Dockerfile

cmd: ["/usr/bin/task-runner"]
```

## Requirements

For local Docker testing:

* Docker
* x86_64 host or compatible Docker environment

For Unikraft testing:

* KraftKit
* QEMU
* x86_64 support

## Verification

A successful run should finish with:

```text
Completed: 3 tasks
```

The expected task results are:

```text
ADD(10, 32) = 42
FIB(10) = 55
SQUARE(7) = 49
```
