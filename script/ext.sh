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
A_LIB=libmlx.a
HEAD="mlx.h\
		mlx_int.h\
		mlx_new_window.h\
		mlx_opengl.h\
		mlx_png.h"
OS=$(uname)

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
fi

if [ "$1" = "" ]
then
	printf $RED$BLD
	echo "Error$NRM$RED: wrong arguments$L_RED\nUsage: sh ext.sh [path_to_cub3d]\n$NRM" >&2
	exit
fi
cd $1 > /dev/null 2>&1 
if [ "$?" != 0 ]
then
	printf $RED$BLD
	echo "Error$NRM$RED: wrong path$L_RED\nUsage: sh ext.sh [path_to_cub3d]\n$NRM" >&2
	exit
fi

if [ "$(ls | grep ext)" = "" ]
then
	mkdir ext
fi
if [ "$(ls | grep lib)" = "" ]
then
	mkdir lib
fi

cd ext
if [ "$OS" = "Linux" ]
then
	touch temp
	apt list --installed > temp 2> /dev/null
	WGET=$(grep -o wget temp)
	GIT=$(grep -o git temp)
	UNZIP=$(grep -o unzip temp)
	rm -f temp

	if [ "$WGET" = "" ]
	then
		printf $BLU
		echo "Installing$BLD wget$NRM$BLU ..."
		sudo apt install wget > /dev/null 2>&1
	fi
	if [ "$GIT" = "" ]
	then
		printf $BLU
		echo "Installing$BLD git$NRM$BLU ..."
		sudo apt install git > /dev/null 2>&1
	fi
	if [ "$UNZIP" = "" ]
	then
		printf $BLU
		echo "Installing$BLD unzip$NRM$BLU ..."
		sudo apt install unzip > /dev/null 2>&1
	fi
	printf $BLU
	echo "Downloading$BLD MinilibX$NRM$BLU ..."
	git clone https://github.com/pbondoer/MinilibX.git > /dev/null 2>&1

	cd MinilibX/X11
	make > /dev/null 2>&1
	cp libmlx.a ../../../lib
	cp mlx.h ../../../inc
	cp mlx_int.h ../../../inc
	cp -r man ../../..
	cd ..
fi

if [ "$OS" = "Darwin" ]
then
	WGET=$(brew list | grep wget)
	GIT=$(brew list | grep git)
	UNZIP=$(brew list | grep unzip)
	printf $BLU
	if [ "$WGET" = "" ]
	then
		echo "Installing$BLD wget$NRM$BLU ..."
		brew install wget > /dev/null 2>&1
	fi
	if [ "$GIT" = "" ]
	then
		printf $BLU
		echo "Installing$BLD git$NRM$BLU ..."
		brew apt install git > /dev/null 2>&1
	fi
	if [ "$UNZIP" = "" ]
	then
		printf $BLU
		echo "Installing$BLD unzip$NRM$BLU ..."
		brew apt install unzip > /dev/null 2>&1
	fi
	echo "Downloading $BLD$A_TAR$NRM$BLU ..."
	wget "https://projects.intra.42.fr/uploads/document/document/1753/minilibx_opengl.tgz" > /dev/null 2>&1
	echo "Downloading $BLD$DY_TAR$NRM$BLU ..."
	wget "https://projects.intra.42.fr/uploads/document/document/1754/minilibx_mms_20200219_beta.tgz" > /dev/null 2>&1

	tar -xf $DY_TAR
	cd $DY_FOLD
	echo "Compiling [$BLD$DY_LIB$NRM$BLU] ..."
	make > /dev/null 2>&1
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

check=$(ls lib | grep libmlx.a)
check2=$(ls inc | grep -e mlx_int.h -e mlx.h -e get_next_line.h | wc -w | tr -d ' \n')
check3=$(ls | grep man)

if [ "$check" = "libmlx.a" ]
then
	if [ "$check2" = "3" ]
	then
		printf $GRN
		echo "Successfully downloaded [$BLD$GNL$NRM$GRN]"
		echo "Successfully compiled [$BLD$A_LIB$NRM$GRN]"
		echo "Successfully imported libraries and includes"
		if [ "$check3" = "man" ]
		then
			echo "Successfully imported MinilibX man"
		else	
			printf "$YLW$BLD"
			echo "Warning:$NRM$YLW Missing man pages for MinilibX" >&2
		fi
		printf $NRM
		exit
	fi
fi

printf $RED
echo "Error: MinilibX compilation failed or missing files$NRM" >&2
