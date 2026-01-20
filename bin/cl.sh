#!/bin/bash

if [[ $(pwd) != "$HOME/cppcp" ]]; then
	echo "Run from $HOME/cppcp"
	exit 1
fi
tempdir=.tmp/
sourcepath=${tempdir}source.txt
usage="
Usage:
        $(basename $0) [-n] [-r] [source1.cpp] [source2.cpp]...

Description:
        Marks source files as completed (default) or removes them and cleans $tempdir
        If no files are provided, tries to mark $sourcepath as completed or remove it.

Options:
        -n	Only cleans $tempdir  Overrules -r.
        -r	Removes files instead of marking them as completed.
"
while getopts 'nr' op; do
	case "$op" in
		n)
			nosource=1
			;;
		r)
			remove=1
			;;
		?)
			echo "$usage"
			exit 1
			;;
	esac
done
shift "$(($OPTIND -1))"
if [[ $nosource -ne 1 ]]; then
	names=()
	if [[ $# -gt 0 ]]; then
		for arg in $@; do
			names+=("${arg%.*}")
		done
	else
		names+=("$(<$sourcepath)")
	fi
	for name in "${names[@]}"; do
		if [[ ! -f "$name.cpp" ]]; then
			echo "$name.cpp not found."
			missing=1
		fi
	done
	if [[ $missing -eq 1 ]]; then
		echo "Exiting due to missing files, no changes made."
		exit 1
	fi
	for name in ${names[@]}; do
		if [[ $remove -eq 1 ]]; then
			rm $name.cpp
			echo "Removed '$name.cpp'"
		else
			mv $name.cpp codeforces
			echo "Moved '$name.cpp' to codeforces/"
		fi
	done
fi
rm -f $tempdir*
echo "Cleaned $tempdir"

