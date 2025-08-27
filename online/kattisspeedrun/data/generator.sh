#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution joshua.cpp

compile gen_print.py
compile gen_randsp.py
compile gen_small.py
compile gen_full.py

samplegroup
sample 1
sample 2
sample 3

group group1 12
limits b_large=1
tc 1
tc 2
tc g1-1 gen_print s=1000 p=2456 a=1 b=100000
tc g1-2 gen_randsp a=1 b=100000
tc g1-3 gen_randsp a=1 b=100000
tc g1-4 gen_randsp a=1 b=100000
tc g1-5 gen_print s=1 p=100000 a=1 b=100000

group group2 18
limits a_large=1
tc g2-1 gen_print s=1000 p=2456 a=100000 b=1
tc g2-2 gen_randsp a=100000 b=1
tc g2-3 gen_randsp a=100000 b=1
tc g2-4 gen_randsp a=100000 b=1
tc g2-5 gen_print s=1 p=100000 a=100000 b=1

group group3 20
limits maxp=1000
tc 3
tc g3-1 gen_small
tc g3-2 gen_small
tc g3-3 gen_small


group group4 50
include_group group1
include_group group2
include_group group3
tc g4-1 gen_full
tc g4-2 gen_full
tc g4-3 gen_full
tc g4-4 gen_full
tc g4-5 gen_full
tc g4-6 gen_full
