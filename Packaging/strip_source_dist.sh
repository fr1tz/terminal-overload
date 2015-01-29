#!/bin/sh

abort()
{
	echo "$*" 2>&1
	echo "Aborting!" 2>&1
	exit 1
}

strip_source_dist()
(
	echo "Stripping content not included in release from source dist..."
	CONTENT=$(cat ./content.txt)
	cd 'dists/source/My Projects/main/game/' || abort
	( mv content content.tmp && mkdir content ) || abort
	(
		cd content.tmp || abort
		for F in "$CONTENT"
		do
			cp --parent -r $F ../content
		done
	)
	rm -r content.tmp || abort
)

strip_source_dist
