#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution olle.cpp

compile gen_print.py
compile gen_rand.py

samplegroup
limits maxa=50 maxnk=50 maxs=50
sample 1
sample 2
sample 3

group group1 5
limits maxa=0 maxnk=5 maxs=5
tc 1
tc g1-1 gen_print in="5 5 5 0"
tc g1-2 gen_print in="5 3 5 0"
tc g1-3 gen_print in="5 5 3 0"
tc g1-4 gen_print in="3 5 3 0"

group group2 15
limits maxa=0 maxnk=50 maxs=50
include_group group1
tc_manual ../manual_data/overflow.in
tc g2-1 gen_print in="50 50 50 0"
tc g2-2 gen_print in="45 50 50 0"
tc g2-3 gen_print in="50 45 50 0"
tc g2-4 gen_print in="50 50 45 0"

group group3 20
limits maxa=50 maxnk=50 maxs=50
include_group group2
tc 2
tc 3
tc g3-1 gen_print in="50 50 50 50"
tc g3-2 gen_print in="45 50 50 50"
tc g3-3 gen_print in="50 45 50 50"
tc g3-4 gen_print in="50 50 45 50"
tc g3-5 gen_print in="50 50 50 45"
tc g3-6 gen_rand hi=50
tc g3-7 gen_rand hi=50

group group4 20
limits maxa=300 maxnk=300 maxs=300
include_group group3
tc g4-1 gen_print in="300 300 300 300"
tc g4-2 gen_print in="295 300 300 300"
tc g4-3 gen_print in="300 295 300 300"
tc g4-4 gen_print in="300 300 295 300"
tc g4-5 gen_print in="300 300 300 295"
tc g4-6 gen_rand hi=300
tc g4-7 gen_rand hi=300

group group5 20
limits maxa=2000 maxnk=2000 maxs=2000
include_group group4
tc g5-1 gen_print in="2000 2000 2000 2000"
tc g5-2 gen_print in="1995 2000 2000 2000"
tc g5-3 gen_print in="2000 1995 2000 2000"
tc g5-4 gen_print in="2000 2000 1995 2000"
tc g5-5 gen_print in="2000 2000 2000 1995"
tc g5-6 gen_rand hi=2000
tc g5-7 gen_rand hi=2000

group group6 20
limits maxa=200000 maxnk=200000 maxs=200000
include_group group5
tc g6-1 gen_print in="200000 200000 200000 200000"
tc g6-2 gen_print in="199995 200000 200000 200000"
tc g6-3 gen_print in="200000 199995 200000 200000"
tc g6-4 gen_print in="200000 200000 199995 200000"
tc g6-5 gen_print in="200000 200000 200000 199995"
tc g6-6 gen_rand hi=200000
tc g6-7 gen_rand hi=200000
