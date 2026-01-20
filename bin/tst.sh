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
        Tests $sourcepath with input set to ${tempdir}inp0.txt ${tempdir}inp1.txt...
        If given, also displays expected output from ${tempdir}out0.txt ${tempdir}out1.txt...
"
if [[ $# -ne 0 ]]; then
	echo "No arguments expected."
	echo "$usage"
	exit 1
fi
if [[ ! -f $sourcepath ]]; then
	echo "$sourcepath not found"
	exit 1
fi
name=$(<$sourcepath)
i=0
inpName=${tempdir}inp
outName=${tempdir}out
if [[ ! -f ${tempdir}$name.out ]]; then
	if [[ ! -f "$name.cpp" ]]; then
		echo "Latest ed-modified file '$name.cpp' missing."
		exit 1
	fi
	. config/compile.sh
	chmod +x ${tempdir}$name.out
fi
while [[ -f "${inpName}${i}.txt" ]]; do
	echo -e "-----------------\n[${i}]INPUT"
	cat "${inpName}${i}.txt"
	echo -e "\n\nOUTPUT"
	cat "${inpName}${i}.txt" | ${tempdir}$name.out
	if [[ -f "${outName}${i}.txt" ]]; then
		echo -e "\n\nEXPECTED OUTPUT"
		cat "${outName}${i}.txt"
	fi
	echo
	i=$((i+1))
done
if [[ $i -eq 0 ]]; then
	echo "No program input files ${tempdir}inp0.txt ${tempdir}inp1.txt... found."
	exit 1
fi

