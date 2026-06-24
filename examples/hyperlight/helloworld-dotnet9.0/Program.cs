using System;
using System.Runtime.InteropServices;

Console.WriteLine("Hello, World! From .NET on Hyperlight!");

// Skip CoreCLR's ~1.5s graceful shutdown — the Hyperlight VM is destroyed anyway.
Exit(0);

[DllImport("libc", EntryPoint = "_exit")]
static extern void Exit(int status);
