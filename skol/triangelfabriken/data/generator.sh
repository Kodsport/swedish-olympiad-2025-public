#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution harry.py

compile gen_rand.py

samplegroup 
sample 1
sample 2
sample 3

group group1 100
include_group sample
tc_manual ../manual_data/secret_01.in
tc_manual ../manual_data/secret_02.in
tc_manual ../manual_data/secret_03.in
tc_manual ../manual_data/secret_04.in
tc_manual ../manual_data/secret_05.in
tc g1-1 gen_rand
tc g1-2 gen_rand
tc g1-3 gen_rand
tc g1-4 gen_rand
tc g1-5 gen_rand mode=Spetsig
tc g1-6 gen_rand mode=Spetsig
tc g1-7 gen_rand mode=Trubbig
tc g1-8 gen_rand mode=Trubbig
tc g1-9 gen_rand mode=Ratvinklig
tc g1-10 gen_rand mode=Ratvinklig