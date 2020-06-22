#!/bin/sh

OS=$(uname)

if [ $OS = "Darwin" ]
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

rm -rf ext
if [ $? = 0 ]
then
	echo "OK"
else
	echo "KO"
fi

rm -rf $to_remove
printf $RED
printf "Removed [$BLD"
printf "ext$NRM$RED]\nRemoved [$BLD"
printf "MinilibX$NRM$RED]\nRemoved [$BLD"
printf "get_next_line$NRM$RED]\nRemoved [$BLD"
printf "man$NRM$RED]\nRemoved [$BLD"
echo "map$NRM$RED]$NRM"
