#!/bin/sh

GRN='\x1b[32m'
RED='\x1b[31m'
L_RED='\x1b[91m'
L_GRN='\x1b[92m'
BLU='\x1b[34m'
BLD='\x1b[1m'
NRM='\x1b[0m'
to_remove="ext\
			inc/mlx*\
			inc/get_next_line.h\
			src/get_next_line*\
			lib/*mlx*\
			man"
cd $1

rm -rf $to_remove
printf $RED
printf "Removed [$BLD"
printf "ext$NRM$RED]\nRemoved [$BLD"
printf "MinilibX$NRM$RED]\nRemoved [$BLD"
echo "get_next_line$NRM$RED]$NRM"
