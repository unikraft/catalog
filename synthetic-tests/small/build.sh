#!/bin/bash

find -type f -name Makefile | while read f; do b=$(dirname "$f"); make -C "$b"; done
