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

if [ "$(ls | grep data)" = "" ]
then
	mkdir data
fi
cd data

printf "The map file must be a valid .cub file\n\n\
Available options:\n  \
-h, --help\t\tShows help message, also ignores any other argument\n\
\t\t\tand does not start the program\n  \
-s, --save\t\tSaves the first rendered image at program start in\n\
\t\t\t<capture> folder\n  \
-b, --bonus\t\tEnables the bonus part.\n\n\
A valid .cub map file must be formatted like this:\n\
<n><s>R <s>[screen x] <s>[screen y]\n\
<n><s>NO <s>[path to north walls texture]<n>\n\
<n><s>SO <s>[path to south walls texture]<n>\n\
<n><s>WE <s>[path to west walls texture]<n>\n\
<n><s>EA <s>[path to east walls texture]<n>\n\
<n><s>S <s>[path to object sprite texture]<n>\n\
<n><s>F <s>[floor color R]<s>,<s>[floor color G]<s>,<s>[floor color B]\n\
<n><s>C <s>[ceiling color R]<s>,<s>[ceiling color G]<s>,<s>[ceiling color B]\n\
<n>[map view from top]<n>\n  0:\t\tfloor\n  1:\t\twall\n  2:\t\tentity\n  \
N/S/W/E:\tUser spawn point and looking direction\n\
The map must be surrounded by '1'\n\n  Example:\n  \
1111111\n  1020001\n  1001N01\n  1001021\n  1111111\n\n\
<s>: arbitrary number of spaces\n\
<n>: arbitrary number of new lines\n\n\
Example: default map file: [default.cub]\n\
R 800 600\n\
NO ./assets/default_north_texture.png\n\
SO ./assets/default_south_texture.png\n\
WE ./assets/default_west_texture.png\n\
EA ./assets/default_east_texture.png\n\
S ./assets/default_sprite_texture.png\n\
F 220,100,0\n\
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
11111111 1111111 111111111111    \n\n\
The order of the parameters at the beggining does not matter,\n\
for example this is a valid .cub file configuration:\n\
S ./path_to_sprite_texture\n\
WE ./path_to_west_texture\n\
R 800 600\n\
NO ./path_to_north_texture\n\
C 225,30,0\n\
EA ./path_to_east_texture\n\
F 220,100,0\n\
SO ./path_to_south_texture\n\n\
Return values:\n  \
0  succes exit\n \
-1  failure exit\n" > help.txt
cd ..
