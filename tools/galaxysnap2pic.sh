#!/bin/bash

# Filename: galaxysnap2pic.sh
# Author: Jay Billings
# Description: This script will create a png image of a GADGET2 galaxy using gnuplot. It requires the read_snapshot.c file
#              from the GADGET2 analysis directory with an xyz data dump defined in do_what_you_want().
#
# Date: 20071201

for item in `ls snapshot_*`
do 
  ./reader $item
  echo "set terminal png;set output '$item.png';set xrange [-250:250];set yrange [-250:250];set xlabel 'x';set ylabel 'y';plot '$item-1.dat','$item-2.dat'" > $item.gnu
  gnuplot $item.gnu
done
