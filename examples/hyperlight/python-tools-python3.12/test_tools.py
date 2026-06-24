#!/usr/bin/env python3
"""Test tool calling via Hyperlight SDK."""
from hyperlight import call_tool

print("Testing tool calling from Python on Hyperlight...")
result = call_tool("echo", message="Hello from inside the VM!")
print(f"Tool returned: {result}")
