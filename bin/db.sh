#!/bin/bash

if [[ $(pwd) != "$HOME/cppcp" ]]; then
	echo "Run from $HOME/cppcp"
	exit 1
fi
tempdir=.tmp/
sourcepath=${tempdir}source.txt
usage="
Usage:
        $(basename $0)

Description:
        Runs lldb on $sourcepath with input set to ${tempdir}inp0.txt
"
if [[ $# -ne 0 ]]; then
	echo "No arguments expected."
	echo "$usage"
	exit 1
fi
if [[ ! -f $sourcepath ]]; then
	echo "$sourcepath not found."
	exit 1
fi

name=$(<$sourcepath)
if [[ ! -f ${tempdir}${name}.out ]]; then
	if [[ ! -f "${name}.cpp" ]]; then
		echo "Latest ed-modified file '${name}.cpp' missing."
		exit 1
	fi
	. config/compile.sh
fi
if [[ ! -f ${tempdir}inp0.txt ]]; then
	echo "No program input file '${tempdir}inp0.txt'."
	exit 1
fi
. config/debug.sh

