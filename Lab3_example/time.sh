#!/bin/bash

for MB in 1 50 500; do
    for BS in 100 4096 8192 16384; do
        echo -e "\n\n$MB $BS result:"
        time ./buffer_size${BS} < ${MB}mb_file_for_buffSize${BS}
    done
done

echo -e "\n\n\npart4 result:\n\n"

for loop in 1 2 2; do
    echo -e "\n\n512mb_file$loop result:"
    time ./buffer_size4096 < 512mb_file${loop}
done

echo -e "\n\n\npart5 result:\n\n"

for loop in 3 4 4; do
    echo -e "\n\n512mb_file$loop result:"
    time ./buffer_size4096_fsync < 512mb_file${loop}
done