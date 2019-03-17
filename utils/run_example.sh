#!/bin/bash
#
# this script will create and run ELM in the example folder
#
# Yingzi Ying 
# yingzi.ying@me.com
#

echo "`date`"
echo "----------------------------------------"
exe=elm
example_folder='./example'
echo "The example is in $example_folder"

echo "----------------------------------------"
echo
echo "Step 1: create $exe."
src_folder='./src'
exe_src=$exe.c
cp $example_folder/input/parameters.h $src_folder

rm -f $example_folder/$exe
mpiCC $src_folder/$exe_src -o $example_folder/$exe

echo "----------------------------------------"
echo
nproc=10
echo "Step 2: run $exe. Number of processes: $nproc."
cd $example_folder
mpiexec -np $nproc $exe