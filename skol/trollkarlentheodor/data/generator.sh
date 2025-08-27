#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution theodor.cpp

compile gen_rand.py

samplegroup
sample 1
sample 2

group group1 20
limits maxa=0
tc_manual ../manual_data/secret_01.in
for i in {1..4}
do
tc g1-$i gen_rand maxh=32 seta=0

done
tc g1-5 gen_rand sets=4 seta=0
tc g1-6 gen_rand sets=1 seta=0


group group2 35
limits maxh=100
include_group sample
#tc_manual ../manual_data/secret_02.in // gets randomly generated
tc_manual ../manual_data/secret_03.in
tc_manual ../manual_data/overflow_small.in
for i in {1..6}
do
tc g2-$i gen_rand maxh=100

done
tc g2-7 gen_rand maxh=100 seta=0
tc g2-8 gen_rand maxh=100 seta=987893125

group group3 5
limits maxa=100000
include_group sample
tc_manual ../manual_data/large_ans.in
for i in {1..6}
do
tc g3-$i gen_rand maxh=100

done
tc g3-7 gen_rand maxh=100 seta=0


group group4 40
include_group group1
include_group group2
include_group group3
tc_manual ../manual_data/secret_04.in
tc_manual ../manual_data/secret_05.in
tc_manual ../manual_data/overflow.in
for i in {1..6}
do
tc g4-$i gen_rand 

done
tc g4-7 gen_rand sets=5 seta=2
tc g4-8 gen_rand sets=2 seta=4
tc g4-9 gen_rand sets=1 seta=1
tc g4-10 gen_rand seta=1000000000
tc g4-11 gen_rand sets=3 seta=873892164
tc g4-12 gen_rand sets=783921798

