#!/bin/sh

OS=$(uname)

if [ "$OS" = "Darwin" ]
then
	GRN='\x1b[32m'
	RED='\x1b[31m'
	L_RED='\x1b[91m'
	L_GRN='\x1b[92m'
	BLU='\x1b[34m'
	BLD='\x1b[1m'
	NRM='\x1b[0m'
else
	GRN='\e[32m'
	RED='\e[31m'
	L_RED='\e[91m'
	L_GRN='\e[92m'
	BLU='\e[34m'
	BLD='\e[1m'
	NRM='\e[0m'
fi
	
to_remove="ext\
			inc/mlx*\
			inc/get_next_line.h\
			src/get_next_line_utils.c\
			src/get_next_line.c\
			lib/*mlx*\
			man\
			map"
cd $1

for i in $to_remove
do
	chmod -R 777 $i > /dev/null 2>&1
	rm -r $i > /dev/null 2> data/temp
	err=$(cat data/temp)
	if [ "$err" = "" ]
	then
		printf $RED
		echo "Removed [$BLD$i$NRM$RED]$NRM"
	fi
done
rm -rf data/temp
