#!/bin/sh

GRN='\x1b[32m'
RED='\x1b[31m'
L_RED='\x1b[91m'
L_GRN='\x1b[92m'
BLU='\x1b[34m'
BLD='\x1b[1m'
YLW='\x1b[33m'
NRM='\x1b[0m'
GNL=get_next_line
DY_TAR=minilibx_mms_20200219_beta.tgz
A_TAR=minilibx_opengl.tgz
DY_FOLD=minilibx_mms_20200219
A_FOLD=minilibx_opengl_20191021
DY_LIB=libmlx.dylib
A_LIB=libmlx.a
HEAD="mlx.h\
		mlx_int.h\
		mlx_new_window.h\
		mlx_opengl.h\
		mlx_png.h"
OS=$(uname)
APT_LIST=0
check=0
check2=0
check3=0

if [ "$1" = "" ]
then
	printf $RED
	echo "Error: wrong arguments$NRM"
	exit
fi

cd $1
if [ "$(ls | grep ext)" = "" ]
then
	mkdir ext
fi

cd ext
printf $BLU
if [ "$OS" = "Linux" ]
then
	GRN='\e[32m'
	RED='\e[31m'
	L_RED='\e[91m'
	L_GRN='\e[92m'
	BLU='\e[34m'
	BLD='\e[1m'
	YLW='\e[33m'
	NRM='\e[0m'
	APT_LIST=$(apt list --installed | grep wget)
	if [ "$APT_LIST" = "" ]
	then
		printf $BLU
		echo "Installing$BLD wget$NRM$BLU ..."
		sudo apt-get install wget > /dev/null 2>&1
	fi
	echo "Downloading$BLD MinilibX$NRM$BLU ..."
	git clone https://github.com/pbondoer/MinilibX.git > /dev/null 2>&1

	cd minilibX/X11
	make > /dev/null 2>&1
	cp libmlx.a ../../../lib
	for file in "$HEAD"
	do
		cp $file ../../../inc
	done
	cd ..
fi

if [ "$OS" = "Darwin" ]
then
	APT_LIST=$(brew list | grep wget)
	if [ "$APT_LIST" = "" ]
	then
		printf $BLU
		echo "Installing$BLD wget$NRM$BLU ...$NRM"
		brew install wget > /dev/null 2>&1
	fi
	echo "Downloading $BLD$A_TAR$NRM$BLU ..."
	wget "https://projects.intra.42.fr/uploads/document/document/1753/minilibx_opengl.tgz" > /dev/null 2>&1
	echo "Downloading $BLD$DY_TAR$NRM$BLU ..."
	wget "https://projects.intra.42.fr/uploads/document/document/1754/minilibx_mms_20200219_beta.tgz" > /dev/null 2>&1

	tar -xf $DY_TAR
	cd $DY_FOLD
	printf $BLU
	echo "Compiling [$BLD$DY_LIB$NRM$BLU] ..."
	make > /dev/null 2>&1
	cp $DY_LIB ../../lib
	cp -r man ../..
	cd ..

	tar -xf $A_TAR
	cd $A_FOLD
	echo "Compiling [$BLD$A_LIB$NRM$BLU] ..."
	make > /dev/null 2>&1
	cp $A_LIB ../../lib
	for file in "$HEAD"
	do
		cp $file ../../inc
	done
fi

cd ..
echo "Downloading $BLD$GNL$NRM$BLU ...$NRM"
git clone https://github.com/2LeoCode/gnl_cub3d $GNL > /dev/null 2>&1

cd $GNL
cp get_next_line.c ../../src
cp get_next_line_utils.c ../../src
cp get_next_line.h ../../inc
cd ../..

check=$(ls lib/libmlx.a)
check2=$(ls inc/mlx* inc/get_next_line.h | wc -w | tr -d ' \n')
check3=$(ls | grep man)

if [ "$check" = "lib/libmlx.a" ]
then
	if [ "$check2" = "6" ]
	then
		printf $GRN
		echo "Successfully compiled [$BLD$GNL$NRM$GRN]"
		echo "Successfully compiled [$BLD$DY_LIB$NRM$GRN] and [$BLD$A_LIB$NRM$GRN]"
		echo "Successfully imported libraries and includes"
		if [ "$check3" = "man" ]
		then
			echo "Successfully imported MinilibX man$NRM"
		else
			printf "$YLW$BLD"
			echo "Warning:$NRM$YLW Missing man pages for MinilibX"
		fi
		exit
	fi
fi

printf $RED
echo "Error: MinilibX compilation failed or missing files$NRM"
