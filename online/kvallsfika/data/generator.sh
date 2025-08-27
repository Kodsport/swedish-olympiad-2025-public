#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution joshua.cpp

compile gen_afford.py
compile gen_rand.py

samplegroup
sample 1
sample 2
sample 3

group group1 20
tc_manual affisch

group group2 5
limits nocategories=1 buyall=1
tc g2-1 gen_afford n=5 k=5 num_categories=5 maxcost=5
tc g2-2 gen_afford n=10 k=10 num_categories=10 maxcost=7
tc g2-3 gen_afford n=15 k=15 num_categories=15 maxcost=8
tc g2-4 gen_afford n=20 k=20 num_categories=20 maxcost=9
tc g2-5 gen_afford k=100000 num_categories=10
tc g2-6 gen_afford k=100000 num_categories=1000
tc g2-7 gen_afford k=100000 num_categories=100000
tc_manual ../manual/exactg2-01.in

group group3 15
limits buyall=1
include_group group2
tc g3-1 gen_afford n=5 k=2 num_categories=5 maxcost=5
tc g3-2 gen_afford n=10 k=3 num_categories=5 maxcost=7
tc g3-3 gen_afford n=15 k=4 num_categories=7 maxcost=8
tc g3-4 gen_afford n=20 k=5 num_categories=12 maxcost=9
tc g3-5 gen_afford k=10 num_categories=10
tc g3-6 gen_afford k=100000 num_categories=1
tc g3-7 gen_afford k=1000 num_categories=10
tc g3-8 gen_afford k=2 num_categories=100000
tc_manual ../manual/exactg3-01.in

group group4 5
limits maxc=1
tc g4-1 gen_rand n=5 maxcost=1 k=5 num_categories=10
tc g4-2 gen_rand n=10 maxcost=1 k=10 num_categories=1
tc g4-3 gen_rand n=15 maxcost=1 k=3 num_categories=3
tc g4-4 gen_rand n=20 maxcost=1 k=2 num_categories=20
tc g4-5 gen_rand n=100000 maxcost=1 k=10 num_categories=10
tc g4-6 gen_rand n=100000 maxcost=1 k=100000 num_categories=1
tc g4-7 gen_rand n=100000 maxcost=1 k=1000 num_categories=10
tc g4-8 gen_rand n=100000 maxcost=1 k=2 num_categories=100000
tc_manual ../manual/exactg4-01.in

group group5 17
limits nocategories=1 maxn=500
tc_manual ../manual/overflow_31
tc_manual ../manual/overflow_32
tc g5-1 gen_rand n=5   k=5   num_categories=1      maxcost=10     
tc g5-2 gen_rand n=10  k=10  num_categories=2      maxcost=20    
tc g5-3 gen_rand n=15  k=15  num_categories=3      maxcost=30   
tc g5-4 gen_rand n=20  k=20  num_categories=4      maxcost=1000 
tc g5-5 gen_rand n=500 k=500 num_categories=1      maxcost=10     
tc g5-6 gen_rand n=500 k=500 num_categories=100000 maxcost=100    
tc g5-7 gen_rand n=500 k=500 num_categories=100000 maxcost=1000   
tc g5-8 gen_rand n=500 k=500 num_categories=100000 maxcost=100000 
tc_manual ../manual/exactg5-01.in


group group6 21
limits nocategories=1
include_group group2
include_group group5
tc g6-1 gen_rand n=100000 k=100000 num_categories=1      maxcost=10     
tc g6-2 gen_rand n=100000 k=100000 num_categories=100000 maxcost=100    
tc g6-3 gen_rand n=100000 k=100000 num_categories=100000 maxcost=1000   
tc g6-4 gen_rand n=100000 k=100000 num_categories=100000 maxcost=100000 
tc_manual ../manual/exactg6-02.in
tc_manual ../manual/exactg6-03.in

group group7 9
limits maxn=500
include_group group5
tc g7-1 gen_rand n=5   k=5 num_categories=3    maxcost=10     
tc g7-2 gen_rand n=10  k=2 num_categories=7    maxcost=11    
tc g7-3 gen_rand n=15  k=5 num_categories=13   maxcost=12   
tc g7-4 gen_rand n=20  k=7 num_categories=8    maxcost=13 
tc g7-5 gen_rand n=500 k=100 num_categories=3  maxcost=10     
tc g7-6 gen_rand n=500 k=10 num_categories=100 maxcost=100    
tc g7-7 gen_rand n=500 k=2 num_categories=500  maxcost=1000   
tc g7-8 gen_rand n=500 k=10 num_categories=3 maxcost=100000 
tc_manual ../manual/exactg7-01.in

group group8 8
include_group sample
include_group group1
include_group group3
include_group group4
include_group group6
include_group group7
tc g8-1 gen_rand n=100000 k=10 num_categories=10 maxcost=10     
tc g8-2 gen_rand n=100000 k=100000 num_categories=1 maxcost=100    
tc g8-3 gen_rand n=100000 k=1000 num_categories=10 maxcost=1000   
tc g8-4 gen_rand n=100000 k=2 num_categories=100000 maxcost=100000 
tc_manual ../manual/exactg8-01.in