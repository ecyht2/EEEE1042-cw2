#!/usr/bin/env bash
vg="valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -s"
FILE="Tan_HongKai_assessment2_EEEE1042"
INCLUDE="TicTacToe.c"

gcc $FILE.c $INCLUDE -o $FILE.o
gcc $FILE.1.c $INCLUDE -o $FILE.1.o
gcc $FILE.2.c $INCLUDE -o $FILE.2.o
gcc $FILE.3.c $INCLUDE -o $FILE.3.o
$vg ./$FILE.2.o
