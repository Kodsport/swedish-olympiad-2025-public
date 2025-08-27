#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution theodor.cpp

compile gen_rand.py

samplegroup 
sample 1
sample 2
sample 3

group group1 40
limits n=100000
include_group sample
tc_manual ../manual_data/secret_01.in
for i in $(seq 1 2);
do
    tc g1-0$i gen_rand maxn=20
done
for i in $(seq 3 4);
do
    tc g1-0$i gen_rand maxn=100000
done
tc g1-05 gen_rand n=99789
tc g1-06 gen_rand n=1
tc g1-07 gen_rand n=10
tc g1-08 gen_rand n=100000
tc g1-09 gen_rand n=10100
tc g1-10 gen_rand n=99999

group group2 60
include_group group1
tc_manual ../manual_data/secret_02.in
tc_manual ../manual_data/secret_03.in
tc_manual ../manual_data/secret_04.in
tc_manual ../manual_data/secret_05.in
for i in $(seq 1 5);
do
    tc g2-0$i gen_rand maxn=1000000000
done
tc g2-06 gen_rand n=200000000
tc g2-07 gen_rand n=1000000000
tc g2-08 gen_rand n=999999999
tc g2-09 gen_rand n=88888899


