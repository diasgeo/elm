#!/bin/bash
operation=$1

folder="ELM*D README.md git.sh"

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
