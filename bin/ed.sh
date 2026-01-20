#!/bin/bash

if [[ $(pwd) != "$HOME/cppcp" ]]; then
	echo "Run from $HOME/cppcp"
	exit 1
fi
tempdir=.tmp/
sourcepath=${tempdir}source.txt
editor="config/editor.sh"
template="config/template.cpp"
compilecommand="config/compile.sh"
usage="
Usage:
        $(basename $0) [-m] [-t] [-h header1 header2...] [source.cpp]

Description:
        Edits source.cpp (if provided) using $editor. If not provided, tries opening $sourcepath instead.
        File extension '.cpp' is not neccessary to be provided, just 'source' works.
        By default, only executable is created. The executable ${tempdir}source.out is not run.
        If 'source.cpp' does not exist, builds it from $template. No headers included by default.

Options:
        -m      runs executable normally. Program input must be fed manually.
        -t      runs bin/tst. Program input from ${tempdir}inp0.txt ${tempdir}inp1.txt...
        -h      includes headers 'header1.hpp'... while building source.cpp.
                'header1' allowed if exactly one file in headers/ matches it. For example, 'header10.h' existing disallows it.
                'source.cpp' must be provided and not be a header, gets rebuilt if it already exists."
headers=()
while getopts 'mth:' op; do
	case "$op" in
		m)
			manualinput=1
			;;
		t)
			runtst=1
			;;
		h)
			useheaders=1
			OPTIND=$(($OPTIND-1))
			if [[ ${!OPTIND} =~ ^- ]]; then
				echo "Expected argument after -h."
				echo "$usage"
				exit 1
			fi
			match="$(ls headers | grep $(basename ${!OPTIND}))"
			matchcount=$(($(echo -n $match | wc -w)))
			if [[ $matchcount -ne 1 ]]; then
				echo "Invalid header '${!OPTIND}', $matchcount matches."
				if [[ $matchcount -gt 1 ]]; then
					echo "$match"
				fi
				echo "Exiting."
				exit 1
			fi
			while [[ $matchcount -gt 0 ]]; do
				headers+=("$match")
				OPTIND=$(($OPTIND+1))
				if [[ $OPTIND -gt $# || ${!OPTIND} =~ ^- ]]; then
					break
				fi
				match="$(ls headers | grep $(basename ${!OPTIND}))"
				matchcount=$(($(echo -n $match | wc -w)))

				if [[ $matchcount -gt 1 ]]; then
					echo "Possible ambiguity for ${!OPTIND}:"
					echo "$match"
					echo "Exiting."
					exit 1
				fi
			done
			;;
		?)
			echo "$usage"
			exit 1
			;;
	esac
done
shift $(($OPTIND-1))

# Setting source file name
if [[ $# -gt 1 ]]; then
	echo "More arguments after source file '$1'."
	echo "Multiple files are not supported."
	echo "Exiting."
	exit 1
elif [[ $# -eq 1 ]]; then
	name=$(echo $1 | cut -d'.' -f1)
	if [[ $useheaders -eq 1 && -f $name.cpp ]]; then
		echo "$name.cpp already exists."
		read -r -p "Rebuild it? [y/N] " response
		response=${response,,}
		if [[ ! "$response" =~ ^(yes|y)$ ]]; then
			echo "Exiting."
			exit 0
		fi
	fi
else
	if [[ $useheaders -eq 1 ]]; then
		echo "Must provide 'source.cpp' while using headers."
		exit 1
	fi
	if [[ ! -f $sourcepath ]]; then
		echo "$sourcepath not found."
		echo "Provide 'source.cpp' to edit."
		exit 1
	fi
	name=$(<$sourcepath)
	if [[ ! -f $name.cpp ]]; then
		echo "$name.cpp does not exist."
		read -r -p "Build it? [y/N] " response
		response=${response,,}
		if [[ ! "$response" =~ ^(yes|y)$ ]]; then
			echo "Exiting."
			exit 0
		fi
	fi
fi
echo "$name" > $sourcepath

# Building source.cpp
if [[ ! -f $name.cpp || $useheaders -eq 1 ]]; then
	solution_location_indicator="// SOLUTION STARTS HERE"
	header_location_indicator="// HEADERS GO HERE"
	header_start_indicator="// IGNORE ABOVE"
	> "$name.cpp"

	line_number=0
	while IFS="" read -r line; do
	if [[ "$line" == "$header_location_indicator" ]]; then
		for header in "${headers[@]}"; do
			copying=0
			while IFS="" read -r hline; do
				if [[ $copying -eq 1 ]]; then
					echo "$hline" >> "$name.cpp"
					line_number=$(($line_number + 1))
				elif [[ "$hline" == "$header_start_indicator" ]]; then
					copying=1
				fi
			done < "headers/$header"
		done
	elif [[ "$line" == "$solution_location_indicator" ]]; then
		solution_start_line=$(($line_number + 1))
	else
		line_number=$((line_number + 1))
		echo "$line" >> "$name.cpp"
	fi
	done < "$template"

	sed -i "1s/.*/\/\/ Solving from line $solution_start_line/" "$name.cpp"
fi

. $editor

set -e
. $compilecommand
chmod +x ${tempdir}$name.out

if [[ $runtst -eq 1 ]]; then
	bin/tst.sh
fi
if [[ $manualinput -eq 1 ]]; then
	${tempdir}$name.out
fi

