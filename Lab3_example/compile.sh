#!/bin/bash

for file in 100 4096 8192 16384;do
    gcc buffer_size${file}.c error.c -o buffer_size${file}
done 