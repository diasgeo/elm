#!/bin/bash
#
# this script will create and run executive in the example folder
#
# Yingzi Ying 
# yingzi.ying@me.com

echo "`date`"
echo "----------------------------------------"
EXAMPLE_folder='./EXAMPLE'
echo "Running example is in folder $EXAMPLE_folder"

echo "----------------------------------------"
echo
echo "Step 1: create executive."
SRC_folder='./SRC'
EXE=ELM3D
cp $EXAMPLE_folder/PARAMETERS.h $SRC_folder

rm -f $EXAMPLE_folder/$EXE
mpiCC $SRC_folder/ELM3D.c -o $EXAMPLE_folder/$EXE

echo "----------------------------------------"
echo
NPROC=4
echo "Step 2: run executive. Number of processes: $NPROC."
cd $EXAMPLE_folder
mpiexec -np $NPROC $EXE
