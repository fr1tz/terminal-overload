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
	cd 'dists/source/My Projects/main/game/' || abort
	( mv content content.tmp && mkdir content ) || abort
	(
		cd content.tmp || abort
		for F in $(find -name INCLUDE_IN_RELEASE)
		do
			DIR=$(dirname $F) && cp --parent -r $DIR ../content
		done
	)
	rm -r content.tmp || abort
)

strip_source_dist
