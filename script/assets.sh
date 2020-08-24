#!/bin/sh

if [ "$(ls | grep assets)" = "" ]
then
	mkdir assets
fi
if [ "$(ls | grep screenshots)" = "" ]
then
	mkdir screenshots
fi
cd assets > /dev/null 2>&1
wget https://lodev.org/cgtutor/files/wolftex.zip > /dev/null 2>&1
unzip wolftex.zip > /dev/null 2>&1
mv pics/* .
rm -rf wolftex.zip pics
cd ..
