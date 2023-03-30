#!/bin/bash

for MB in 1 50 500; do
    for BS in 100 4096 8192 16384; do
        count=$(((MB * 1024 * 1024)/BS))
        dd if=/dev/zero of=${MB}mb_file_for_buffSize${BS} bs=1024 count=${count}
    done
done

for loop in 1 2 3 4; do
    count=$((512 * 1024))
    dd if=/dev/zero of=512mb_file${loop} bs=1024 count=${count}
done