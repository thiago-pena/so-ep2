#!/bin/bash

# script

make

for i in `seq 1 30`
do
    ./ep2 250 100 -benchmark $i
done
for i in `seq 1 30`
do
    ./ep2 500 100 -benchmark $i
done
for i in `seq 1 30`
do
    ./ep2 1000 100 -benchmark $i
done
