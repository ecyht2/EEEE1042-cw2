#!/bin/sh
# Setting up stdin.txt file
echo 0 2 2 > stdin.txt
# Setting up stdin.txt file based on arguments
case $1 in
	1) echo 0 2 2 > stdin.txt ;;
	2) echo 0 2 1 > stdin.txt ;;
	3) echo 0 1 1 > stdin.txt ;;
esac

# Creating Data Directories
if [ ! -d Data ]; then
	mkdir Data
	mkdir Data/"Smart vs Smart"
	mkdir Data/"Smart vs Random"
	mkdir Data/"Random vs Random"
fi

# Setting up Situations
case $1 in
	1) mode="Smart vs Smart" ;;
	2) mode="Smart vs Random" ;;
	3) mode="Random vs Random" ;;
esac

# Getting all the data
for x in {1..1000}; do
	./Tan_HongKai_assessment2_EEEE1042.o < stdin.txt > Data/$mode/Experiment-$x
done
