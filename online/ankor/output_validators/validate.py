#!/usr/bin/env python3
# usage: python3 validator.py input_file correct_output output_dir < contestants_output

import sys

def die(msg):
    print(msg)
    exit(43)

def accept():
    exit(42)

if len(sys.argv) < 4:
    exit(1)

answer_file = sys.argv[2]
output_dir = sys.argv[3]

with open(answer_file) as f:
    judge_k, judge_m = f.read().split()

try:
    user_k, user_m = sys.stdin.read().strip().split()
except:
    die('unable to read stdin')

input_file = sys.argv[1]
with open(input_file, "r") as f:
    n = int(f.readline())
    points = [[int(i) for i in f.readline().split()] for j in range(n*2)]


def isabove(k, m, x, y):
    from fractions import Fraction

    k = Fraction(k)
    m = Fraction(m)
    if k > Fraction("5e9") or k < Fraction("-5e9") \
      or m > Fraction("5e9") or m < Fraction("-5e9"):
        raise AssertionError("Too large k or m")
    x = Fraction(x)
    y = Fraction(y)

    return y > (k * x + m)


def test_line_isvalid(k, m):
    above_cnt = 0
    for p in points:
        above_cnt += isabove(k, m, p[0], p[1])
    
    if above_cnt != n:
        raise AssertionError("")

try:
    test_line_isvalid(judge_k, judge_m)
except:
    raise AssertionError("Judge failed")

if len(user_k) > 50 or len(user_m) > 50:
    die('Too long output')

try:
    test_line_isvalid(user_k, user_m)
except:
    die('Did not split points evenly or failed to parse')

accept()

