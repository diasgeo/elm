#!/bin/bash
operation=$1

folder="../elm2d ../elm3d ../README.md ../utils"

if [ $operation == 'push' ]
then
git add $folder
git commit -m "pushing $folder"
git push origin master
elif [ $operation == 'pull' ]
then
git commit -m "pulling $folder"
git pull origin master
fi
