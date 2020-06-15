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
touch default.cub
printf "R 1920 1080\n\
NO ./path_to_the_north_texture\n\
SO ./path_to_the_south_texture\n\
WE ./path_to_the_west_texture\n\
EA ./path_to_the_east_texture\n\
S ./path_to_the_sprite_texture\n\
F 220,100,0\
C 225,30,0\n        \
1111111111111111111111111\n        \
1000000000110000000000001\n        \
1011000001110000002000001\n        \
1001000000000000000000001\n\
111111111011000001110000000000001\n\
100000000011000001110111111111111\n\
11110111111111011100000010001    \n\
11110111111111011101010010001    \n\
11000000110101011100000010001    \n\
10002000000000001100000010001    \n\
10000000000000001101010010001    \n\
11000001110101011111011110N0111  \n\
11110111 1110101 101111010001    \n\
11111111 1111111 111111111111    " > default.cub
printf $GRN$BLD
echo "Cub3D$NRM$GRN: Generated default map"
