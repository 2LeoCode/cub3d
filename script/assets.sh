#!/bin/sh

if [ "$(ls | grep assets)" = "" ]
then
	mkdir assets
fi
cd assets > /dev/null 2>&1
wget https://lodev.org/cgtutor/files/wolftex.zip > /dev/null 2>&1
unzip wolftex.zip > /dev/null 2>&1
mv pics/* .
rm -rf wolftex.zip pics
git clone https://github.com/2LeoCode/img_for_cub3d.git > /dev/null 2>&1
mv img_for_cub3d/* .
rm *rf img_for_cub3d
cd ..
