# Node Puppeteer Example

This directory contains a simple [Puppeteer](https://www.prisma.io/) example (using JavaScript for [Node](https://nodejs.org/en/)) running with Unikraft in binary compatibility mode.
The image opens up a server and provides routes for results.

**Note**: This is not currently running.

## Quick Run

Use `kraft` to run the image:

```console
kraft run -M 2048M
```

Once executed, it will query a remote web page and generate a PDF version of it.
