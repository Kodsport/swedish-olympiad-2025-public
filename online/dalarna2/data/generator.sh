#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution theodor.cpp

compile gen_rand.py 
compile gen_line.py 
compile gen_star.py

samplegroup
sample 1
sample 2
sample 3

group group1 8
limits line=1
tc 1
tc g1-1 gen_line n=8136 pmax=371268
tc g1-2 gen_line n=2000
tc g1-3 gen_line n=89127
tc g1-4 gen_line
tc g1-5 gen_line n=99987 pmax=1
tc g1-6 gen_line n=7 pmax=5

group group2 11
limits pmin=1 pmax=1
tc g2-1 gen_rand n=100 pmin=1 pmax=1
tc g2-2 gen_rand n=20000 pmin=1 pmax=1
tc g2-3 gen_rand n=100000 pmin=1 pmax=1
tc g2-4 gen_rand pmin=1 pmax=1
tc g2-5 gen_rand pmin=1 pmax=1


group group3 9
limits pmax=1
include_group group2
tc g3-1 gen_rand n=100 pmax=1
tc g3-2 gen_rand n=20000 pmax=1
tc g3-3 gen_rand n=100000 pmax=1
tc g3-4 gen_rand pmax=1
tc g3-5 gen_rand pmax=1
tc g1-5

group group4 12
limits nmax=7 pmax=5
include_group sample
tc g4-1 gen_rand n=4 pmax=5
tc g4-2 gen_rand n=7 pmax=5
tc g4-3 gen_rand n=7 pmax=5
tc g4-4 gen_rand n=7 pmax=5
tc_manual ../manual/harrykiller03.in
tc_manual ../manual/harrykiller04.in #
tc g1-6 

group group5 14
limits nmax=100 pmax=100
include_group group4
tc_manual ../manual/harrykiller01.in #
tc_manual ../manual/harrykiller02.in #
tc g5-1 gen_rand n=50 pmax=100
tc g5-2 gen_rand n=100 pmax=100 
tc g5-3 gen_rand n=90 pmax=100
tc g5-4 gen_rand n=100 pmax=100
tc g5-5 gen_rand n=100 pmin=80 pmax=100
tc g5-6 gen_line n=100 pmax=10 partLine=0.5
tc g5-7 gen_star n=100 pmax=100 amountStars=1 partStar=0.8
tc g5-8 gen_star n=100 pmax=100 amountStars=10 partStar=0.6
tc g5-9 gen_line n=100 pmax=100 partLine=0.9

group group6 15
limits nmax=1000
include_group group5
tc g6-1 gen_rand n=500 pmax=10000
tc g6-2 gen_rand n=1000 pmax=100000
tc g6-3 gen_rand n=900 
tc g6-4 gen_rand n=1000 
tc g6-5 gen_rand pmin=100000000 n=1000 
tc g6-6 gen_line n=1000 pmax=1000 partLine=0.4
tc g6-7 gen_star n=1000 pmax=1000 amountStars=1 partStar=0.8
tc g6-8 gen_star n=1000 pmax=1000 amountStars=3 partStar=0.6
tc g6-9 gen_line n=1000 pmax=1000 partLine=0.9

group group7 31
include_group group1
include_group group3
include_group group6
tc g7-1 gen_rand pmax=10
tc g7-2 gen_rand 
tc g7-3 gen_rand 
tc g7-4 gen_rand 
tc g7-5 gen_rand pmin=100000000
tc g7-6 gen_line partLine=0.8
tc g7-7 gen_line partLine=0.3
tc g7-8 gen_star amountStars=1 partStar=0.7
tc g7-9 gen_star amountStars=10 partStar=0.9
tc g7-10 gen_star amountStars=4 partStar=0.3
