#!/usr/bin/python
from sys import stdin
import re, sys

line = stdin.readline()
c, r = map(int, line.split())
goals = 0
for _ in range(r):
    line = stdin.readline()
    for c in line:
        if c == 'M':
            goals += 1

assert goals == 1

sys.exit(42)
