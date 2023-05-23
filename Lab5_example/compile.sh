#!/bin/bash

dd if=/dev/zero of=100mb_file bs=1024 count=102400
echo -e "dd complete.\n"

cd 5-4
./fig.sh
echo -e "makefile_5_4 complete.\n"
cd ../

cd 5-5
./fig.sh
echo -e "makefile_5_5 complete.\n"
cd ../

echo -e "\n\ntime fig5-4\n"
time ./5-4/exe_fig5_4 < 100mb_file
time ./5-4/fgets < 100mb_file

echo -e "\n\ntime fig5-5\n"
echo -e "fully_buffer\n"
time ./5-5/fully_buffer < 100mb_file
echo -e "line_buffer\n"
time ./5-5/line_buffer < 100mb_file
echo -e "no_buffer\n"
time ./5-5/no_buffer < 100mb_file