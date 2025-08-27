#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution ../generate_secret.cpp

compile generate.py

group group1 7
limits k=510
tc g1-1 generate k=510 mode=random   seed=10
tc g1-2 generate k=510 mode=random   seed=20
tc g1-3 generate k=510 mode=random   seed=30
tc g1-4 generate k=510 mode=size1    seed=40
tc g1-5 generate k=510 mode=evenends seed=60
tc g1-6 generate k=510 mode=lefteven seed=70

group group2 11
limits k=410
tc g2-1 generate k=410 mode=random   seed=10
tc g2-2 generate k=410 mode=random   seed=20
tc g2-3 generate k=410 mode=random   seed=30
tc g2-4 generate k=410 mode=size1    seed=40
tc g2-5 generate k=410 mode=evenends seed=60
tc g2-6 generate k=410 mode=lefteven seed=70

group group3 21
limits k=310
tc g3-1 generate k=310 mode=random   seed=10
tc g3-2 generate k=310 mode=random   seed=20
tc g3-3 generate k=310 mode=random   seed=30
tc g3-4 generate k=310 mode=size1    seed=40
tc g3-5 generate k=310 mode=evenends seed=60
tc g3-6 generate k=310 mode=lefteven seed=70

group group4 0
limits k=310 evenends=1
tc g3-5

group group5 0
limits k=310 lefteven=1
tc g3-6

group group6 5
limits k=250 size1=1
tc g6-1 generate k=250 mode=size1 seed=40

group group7 25
limits k=250
tc g7-1 generate k=250 mode=random   seed=10
tc g7-2 generate k=250 mode=random   seed=20
tc g7-3 generate k=250 mode=random   seed=30
tc g6-1
tc g7-5 generate k=250 mode=evenends seed=60
tc g7-6 generate k=250 mode=lefteven seed=70

group group8 13
limits k=210
tc g8-1 generate k=210 mode=random   seed=10
tc g8-2 generate k=210 mode=random   seed=20
tc g8-3 generate k=210 mode=random   seed=30
tc g8-4 generate k=210 mode=size1    seed=40
tc g8-5 generate k=210 mode=evenends seed=60
tc g8-6 generate k=210 mode=lefteven seed=70

group group9 18
limits k=150
tc g9-1 generate k=150 mode=random   seed=10
tc g9-2 generate k=150 mode=random   seed=20
tc g9-3 generate k=150 mode=random   seed=30
tc g9-4 generate k=150 mode=size1    seed=40
tc g9-5 generate k=150 mode=evenends seed=60
tc g9-6 generate k=150 mode=lefteven seed=70
