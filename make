#!/usr/bin/env bash
vg="valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -s"
FILE="Tan_HongKai_assessment2_EEEE1042"

gcc -o $FILE.o $FILE.c
gcc -o $FILE.1.o $FILE.1.c
gcc -o $FILE.2.o $FILE.2.c
gcc -o $FILE.3.o $FILE.3.c
$vg ./$FILE.2.o
