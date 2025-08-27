#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution victor.cpp

compile gen_rand.py
compile gen_yes.py

samplegroup
limits diff=-1 unique=0
sample 1
sample 2
sample 3

group group1 20
limits diff=-1 unique=1
tc_manual ../manual_data/secret_11.in
tc_manual ../manual_data/secret_12.in
tc_manual ../manual_data/max1.in
for i in {1..2}
do
tc g1-$i gen_rand maxlen=26 diff=-1 unique=1
done
for i in {3..4}
do
tc g1-$i gen_yes maxlen=26 diff=-1 unique=1
done

group group2 20
limits diff=1 unique=0
tc_manual ../manual_data/secret_21.in
tc_manual ../manual_data/secret_22.in
tc max1
for i in {1..2}
do
tc g2-$i gen_rand maxlen=32 diff=1 unique=0
done
for i in {3..4}
do
tc g2-$i gen_yes maxlen=26 diff=1 unique=1
done

group group3 20
limits diff=2 unique=0
tc_manual ../manual_data/secret_31.in
tc_manual ../manual_data/secret_32.in
tc_manual ../manual_data/max2.in
for i in {1..2}
do
tc g3-$i gen_rand maxlen=32 diff=2 unique=0
done
for i in {3..4}
do
tc g3-$i gen_yes maxlen=26 diff=2 unique=1
done

group group4 40
limits diff=-1 unique=0
include_group group1
include_group group2
include_group group3
include_group sample
tc_manual ../manual_data/secret_41.in
tc_manual ../manual_data/secret_42.in
tc_manual ../manual_data/secret_51.in
tc_manual ../manual_data/secret_52.in
tc_manual ../manual_data/max3.in
for i in {1..7}
do
tc g4-$i gen_rand maxlen=32 diff=-1 unique=0
done
for i in {8..15}
do
tc g4-$i gen_rand maxlen=32 diff=-1 unique=0
done

