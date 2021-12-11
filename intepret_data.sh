#!/usr/bin/env bash

output=$1
xWins=0
xLost=0
tie=0

getData(){
    for x in $(ls Data/"$1"); do
        line=$(tail -n 1 "Data/$1/$x")

        if [ "$line" = "Player x won!" ]; then
            xWins=$(expr $xWins + 1)
        elif [ "$line" = "Player o won!" ]; then
            xLost=$(expr $xLost + 1)
        else
            tie=$(expr $tie + 1)
        fi
    done
}

resetData(){
    xWins=0
    xLost=0
    tie=0
}

printData(){
    print="$1
x wins $xWins amount of times
x losts $xLost amount of times
It is a tie $tie amount of times"
    if [ -z "$2" ]; then
        echo "$print"
    else
        echo ""
    fi
}

# Smart vs Smart
getData "Smart vs Smart"
printData "Smart vs Smart" "$1"
resetData
# Smart vs Random
getData "Smart vs Random"
printData "Smart vs Random" "$1"
resetData
# Random vs Random
getData "Random vs Random"
printData "Random vs Random" "$1"
