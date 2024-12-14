#
# Imported from the operating systems class.
#

#!/usr/bin/env python 3

import sys
import subprocess

def main():
	proc_reader = subprocess.Popen(["./reader"], stdin=subprocess.PIPE)
	proc_writer = subprocess.Popen(["./writer"], stdout=subprocess.PIPE)
	message = proc_writer.stdout.read()
	proc_reader.stdin.write(message)


if __name__ == "__main__":
	sys.exit(main())
