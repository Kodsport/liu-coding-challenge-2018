#!/usr/bin/python
from sys import stdin
import re, sys

line = stdin.readline()
assert re.match("[a-z]{1,15}( [a-z]{1,15})+\n", line)
w = line.split()
assert len(w) <= 100

line = stdin.readline()
assert len(line) == 0
sys.exit(42)
