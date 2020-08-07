#!/bin/sh

if [ "$(ls | grep assets)" = "" ]
then
	mkdir assets
fi
cd assets > /dev/null 2>&1
wget https://lodev.org/cgtutor/files/wolftex.zip > /dev/null 2>&1
tar -xf wolftex.zip
rm -rf wolftex.zip
cd ..
