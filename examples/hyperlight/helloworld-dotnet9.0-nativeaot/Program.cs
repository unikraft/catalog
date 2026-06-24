using System;
using System.Runtime.InteropServices;

Console.WriteLine("Hello, World! From .NET NativeAOT on Hyperlight!");

// Bypass runtime shutdown (thread join hangs/crashes in unikernel)
[DllImport("*", EntryPoint = "_exit")]
static extern void NativeExit(int status);
NativeExit(0);
