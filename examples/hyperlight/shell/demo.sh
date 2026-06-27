#!/bin/sh
echo "Hello from Shell on Hyperlight!"
echo ""
echo "--- File operations ---"
mkdir -p /tmp/workspace
echo "hyperlight" > /tmp/workspace/hello.txt
cat /tmp/workspace/hello.txt
ls /tmp/workspace/
echo ""
echo "--- Text processing ---"
echo "alpha" > /tmp/workspace/data.txt
echo "bravo" >> /tmp/workspace/data.txt
echo "charlie" >> /tmp/workspace/data.txt
cat /tmp/workspace/data.txt
wc -l /tmp/workspace/data.txt
echo ""
echo "--- Arithmetic ---"
a=42
b=13
echo "  $a + $b = $(($a + $b))"
echo "  $a * $b = $(($a * $b))"
echo ""
echo "Done!"
