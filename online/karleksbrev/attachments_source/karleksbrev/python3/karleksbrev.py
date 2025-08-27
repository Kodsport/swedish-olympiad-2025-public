#!/usr/bin/python3
def encode(S: str) -> str:
    E = []
    for c in S:
        E.append(c*5)
    return "".join(E)

# Note: this E is E after it has been corrupted
def decode(E: str) -> str:
    ret = ""
    while len(E):
        chunk = E[:5]
        E = E[5:]
        ret += chunk[2]
    return ret
