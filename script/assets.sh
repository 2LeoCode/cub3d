#!/bin/sh

BLU='\x1b[34m'
BLD='\x1b[1m'
NRM='\x1b[0m'

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
