#!/bin/bash

#compile program

if [ $# != 1 ]; then

    echo "require only one argument"
    exit 0

fi

test -e $1 && gcc $1.c error.c -o $1 -Wall || echo "File Not exist"