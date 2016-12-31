#!/bin/bash

if [[ $# -ne 1 ]] 
    then echo "kpush.sh usage: {file to push}"
	exit 0
fi

git add "$1"
git commit -m "kpush"
git push origin

