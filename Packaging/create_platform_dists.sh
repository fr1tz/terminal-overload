#!/bin/sh

abort()
{
	echo "$*" 2>&1
	echo "Aborting!" 2>&1
	exit 1
}

create_platform_dists()
(
	echo "Creating platform distributions..."
	cd dists/ || abort

	test -d linux && rm -r linux
	test -d win32 && rm -r win32

	cp -r 'source/My Projects/main/game' linux || abort
	FIND_ARGS="linux"
	for EXT in dmp psd src.png max xcf blend dae
	do
		FIND_ARGS="$FIND_ARGS -name *.$EXT -execdir rm {} ; -o"
	done
	FIND_ARGS="$FIND_ARGS -false"
	#echo "find $FIND_ARGS"
	find $FIND_ARGS
	cp -r linux win32 || abort

	rm linux/*.dll || abort
	rm win32/lib* || abort
	cp ../bins/linux/* linux/ || abort
	cp ../bins/win32/* win32/ || abort
)

create_platform_dists

