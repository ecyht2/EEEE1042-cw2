#!/usr/bin/env bash
vg="valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -s"
FILE="Tan_HongKai_assessment2_EEEE1042"
INCLUDE="TicTacToe.c Gui.c"
ARGS="`pkg-config --libs --cflags gtk4`"

gcc $FILE.c $INCLUDE  -o $FILE.out $ARGS
gcc $FILE.1.c $INCLUDE -o $FILE.1.out $ARGS
gcc $FILE.2.c $INCLUDE -o $FILE.2.out $ARGS
gcc $FILE.3.c $INCLUDE -o $FILE.3.out $ARGS
#gcc gui.c -o gui.out `pkg-config --libs --cflags gtk4`
./$FILE.out
