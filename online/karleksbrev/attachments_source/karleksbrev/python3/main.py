#!/usr/bin/env python3
#
# Testing tool for the task Love Letter.
# Your solution MUST be named karleksbrev.py and placed
# in the same folder as main.py.
#
# Usage:
#
#   python3 main.py [--silent] < input.txt
#
# input.txt uses the following format:
#
# N K
# S
# L R
# Where N is the length of S,
# K is the maximum length of a message that the encoder may produce,
# S is the message that should be sent,
# L and R denote the interval that should be flipped.
# More precisely, the judge will corrupt m[L], m[L+1], ..., m[R]
#
# Example input:
#
# 5 10
# 01011
# 1 3
#
#
# If --silent is passed, the communication output will not be printed.
#
# The tool is provided as-is, and you should feel free to make
# whatever alterations or augmentations you like to it. Notably,
# this is not the grader used in Kattis. This grader is also more informative
# as to how your program failed compared to Kattis.

import sys

from karleksbrev import encode, decode

def main():
    silent = False
    args = sys.argv[1:]
    if args and args[0] == "--silent":
        args = args[1:]
        silent = True
    if args == ["-h"]:
        print("Usage:", sys.argv[0], "[--silent] ... < input.txt")
        sys.exit(0)
    

    N, K = [int(i) for i in input().split()]
    S = input()
    L, R = [int(i) for i in input().split()]

    # Sanity check input
    if len(S) != N:
        print(f"[X] Error: {len(S)=} does not match {N=}")
        sys.exit(1)
    for c in S:
        if not c in ['0', '1']:
            print(f"[X] Error: {S=} contains character \"{c}\", which is not 0 or 1")
            sys.exit(1)

    if not silent:
        print(f"[*] Running with {N=}, {K=}, {S=}, {L=}, {R=}")

    # Encode S
    E = encode(S)
    if not silent:
        print(f"[*] {S=}, encode(S)={E}")

    # Sanity check E
    if len(E) == 0:
        print(f"[X] Error: encoder gave an empty E for S={S}")
        sys.exit(1)
    if len(E) > K:
        print(f"[X] Error: encoder gave too long E. {len(E)=} > {K=}")
        sys.exit(1)
    for c in E:
        if not c in ['0', '1']:
            print(f"[X] Error: encoder gave E containing character \"{c}\", which is not 0 or 1")
            sys.exit(1)

    if L < 0 or R < 0 or L >= len(E) or R>=len(E):
        print(f"[X] Error: {L=} or {R=} is out of bounds for {len(E)=}")
        sys.exit(1)
    
    # Corrupt an interval
    E = [c for c in E]
    for i in range(L,R+1):
        if E[i]=='0':
            E[i]='1'
        else:
            E[i]='0'
    E = "".join(E)

    if not silent:
        print(f"[*] {E=} after corrupting")


    # Check that the decoder can decode the corrupted E
    decoded = decode(E)
    if decoded != S:
        print(f"[X] Error: decoder did not find S. E after corrupting={E}, {S=}, decode(E)={decoded}")
        sys.exit(1)

    if not silent:
        print(f"[*] decode(E)={E}")

    print(f"Success! {N=} {len(E)=}")

if __name__ == "__main__":
    main()
