#!/bin/sh

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

if [ "$(ls | grep assets)" = "" ]
then
	printf $BLU
	echo "Downloading$BLD assets$NRM$BLU ...$NRM"
	git clone https://github.com/2LeoCode/cub3dAssets.git assets > /dev/null 2>&1
else
	cd assets
	git pull > /dev/null 2>&1
	cd ..
fi
if [ "$(ls | grep screenshots)" = "" ]
then
	mkdir screenshots
fi
