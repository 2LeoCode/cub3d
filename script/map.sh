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

if [ $1 = "" ]
then
	printf $RED$BLD
	echo "Error$NRM$RED: Wrong input$L_RED\nUsage: sh map.sh [path_to_cub3d]$NRM" >&2
	exit
fi

cd $1 > /dev/null 2>&1

if [ "$?" != 0 ]
then
	printf $RED$BLD
	echo "Error$NRM$RED: wrong path$L_RED\nUsage: sh map.sh [path_to_cub3d]\n$NRM" >&2
	exit
fi

cd map
printf "R 800 600\n\
NO ./assets/redbrick.xpm\n\
SO ./assets/wood.xpm\n\
WE ./assets/greystone.xpm\n\
EA ./assets/mossy.xpm\n\
S ./assets/barrel.xpm\n\
F 85,85,85\n\
C 85,55,0\n\
11111111111111\n\
10200102000001\n\
10000100011001\n\
11101100001001\n\
10000000200001\n\
100E0000000201\n\
11111111111111" > default.cub
cd ..
printf $GRN$BLD
echo "Cub3D$NRM$GRN: Generated default map"
