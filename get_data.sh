#!/bin/sh
# Making Sure there is a situation enterted
if [ -z "$1" ]; then
	echo No Situation is Enterted
	echo Usage: ./get_data situation executable
	exit 1
fi

if [ $1 != 1 -a $1 != 2 -a $1 != 3 ]; then
	echo Invalid Situation Entered
	echo Usage: ./get_data situation executable
	exit 1
fi

# Making sure there is an executable entered
if [ -z "$2" ]; then
	echo No Executable Entered
	echo Usage: ./get_data situation executable
	exit 1
fi

# Setting up executable
executable=$2

# Setting up stdin.txt file based on arguments
case $1 in
	1) echo 0 2 2 > stdin.txt ;;
	2) echo 0 2 1 > stdin.txt ;;
	3) echo 0 1 1 > stdin.txt ;;
esac

# Creating Data Directories
if [ ! -d Data ]; then
	mkdir Data
else
	if [ ! -d Data/"Smart vs Smart" ]; then
		mkdir Data/"Smart vs Smart"
	elif [ ! -d Data/"Smart vs Random" ]; then
		mkdir Data/"Smart vs Random"
	elif [ ! -d Data/"Random vs Random" ]; then
		mkdir Data/"Random vs Random"
	fi
fi

# Setting up Situations
case $1 in
	1) mode="Smart vs Smart" ;;
	2) mode="Smart vs Random" ;;
	3) mode="Random vs Random" ;;
esac

# Getting all the data
for x in {1..1000}; do
	./$executable < stdin.txt > Data/$mode/Experiment-$x
done
