#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution joshua.cpp

compile gen_rand.py

MAX_C=10000000
samplegroup
limits lb=-$MAX_C ub=$MAX_C
sample 1
sample 2
sample 3
sample 4


group group1 20
limits lb=0 ub=0
tc 3
tc g1-1 gen_rand n=30 lb=0 ub=0
tc g1-2 gen_rand n=30 lb=0 ub=0
tc g1-3 gen_rand n=30 lb=0 ub=0

group group2 30
limits lb=0 ub=$MAX_C
include_group group1
tc g2-1 gen_rand n=30 lb=0 ub=$MAX_C
tc g2-2 gen_rand n=30 lb=0 ub=$MAX_C
tc g2-3 gen_rand n=30 lb=0 ub=$MAX_C

group group3 50
limits lb=-$MAX_C ub=$MAX_C
include_group sample
include_group group2
tc g3-1 gen_rand n=30 lb=-$MAX_C ub=$MAX_C
tc g3-2 gen_rand n=30 lb=-$MAX_C ub=$MAX_C
tc g3-3 gen_rand n=30 lb=-$MAX_C ub=$MAX_C
tc g3-4 gen_rand n=30 lb=-$MAX_C ub=$MAX_C
tc g3-5 gen_rand n=30 lb=-$MAX_C ub=$MAX_C
tc g3-6 gen_rand n=30 lb=-$MAX_C ub=$MAX_C
