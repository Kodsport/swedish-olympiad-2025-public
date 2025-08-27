#!/usr/bin/python3

import sys
import random
import math
from random import randint
from string import ascii_lowercase

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default


class trie:
    def __init__(self) -> None:
        self.next = []
        self.hist = set()

    def initReal(self):
        self.next = [trie() for i in range(26)]

    def query(self, length, p):
        if length == 0: return ""
        if random.uniform(0, 1)<p or not len(self.hist): 
            index = randint(0, 25)
            if index not in self.hist: self.next[index].initReal()
            self.hist.add(index)
            return chr(ord('a')+index)+self.next[index].query(length-1, p)
        index = random.choice(list(self.hist))
        return chr(ord('a')+index)+self.next[index].query(length-1, p)
        



random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n', 100))
m = int(cmdlinearg('m', 100))
p = float(cmdlinearg('p', 0.1)) # sannolikhet random ny
prefix_len = int(cmdlinearg('l', 0))
r = bool(cmdlinearg('r', False))

print(n, m)
t = trie()

seen = set()

t.initReal()
for i in range(m):
    while True:
        prefix = "".join(random.choice(ascii_lowercase) for _ in range(prefix_len))
        s = (prefix+t.query(randint(prefix_len+1,n)-prefix_len, p))[::(-1 if r else 1)]
        if s in seen:
            continue
        seen.add(s)
        print(s)
        break
