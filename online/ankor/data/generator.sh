#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited # vad gör detta?

use_solution theodorSafe.cpp

# Möjligen Jobbiga testfall
# cpp rand() lutning intersectar 2
# gör grader adaptiv???
# ha punkter på x=0 och y=0 där lösningen skulle kunna vara (float problem)
# det folk har skrivit här https://github.com/Kodsport/swedish-olympiad-problemsetting/issues/80


compile gen_rand.py

samplegroup
sample_manual 1
sample_manual 2
sample_manual 3

group group1 15
limits n=1
tc 1
tc_manual ../manual/g1_line1
tc_manual ../manual/g1_line2
tc_manual ../manual/g1_line3
tc g1-1 gen_rand n=1
tc g1-2 gen_rand n=1
tc g1-3 gen_rand n=1
tc g1-4 gen_rand n=1

group group2 15
limits x=0
tc g2-1 gen_rand n=10 x=0
tc g2-2 gen_rand n=100 x=0
tc g2-3 gen_rand n=1000 x=0
tc g2-4 gen_rand n=100000 x=0
tc g2-5 gen_rand n=100000 x=0

group group3 15
limits xmax=1
include_group group2
tc g3-1 gen_rand n=10 xmax=1
tc g3-2 gen_rand n=100 xmax=1
tc g3-3 gen_rand n=1000 xmax=1
tc g3-4 gen_rand n=100000 xmax=1
tc g3-5 gen_rand n=100000 xmax=1

group group4 15
limits n=2
tc 2
tc_manual ../manual/g4_line1
tc_manual ../manual/g4_line2
tc_manual ../manual/g4_line3
tc g4-1 gen_rand n=2
tc g4-2 gen_rand n=2
tc g4-3 gen_rand n=2
tc g4-4 gen_rand n=2
tc g4-5 gen_rand n=2

group group5 20
limits nmax=1000
include_group group1
include_group group4
tc 3
tc g5-1 gen_rand n=100
tc g5-2 gen_rand n=1000
tc g5-3 gen_rand n=1000
tc g5-4 gen_rand n=1000
tc g5-5 gen_rand n=1000
tc g5-6 gen_rand n=1000 xmax=100 ymax=100

group group6 20
include_group group3
include_group group5
tc g6-1 gen_rand n=100000
tc g6-2 gen_rand n=100000
tc g6-3 gen_rand n=100000
tc g6-4 gen_rand n=100000
tc g6-5 gen_rand n=100000
tc g6-6 gen_rand n=100000 xmax=1000 ymax=1000
tc g6-7 gen_rand n=100000 xmax=500 ymax=500
