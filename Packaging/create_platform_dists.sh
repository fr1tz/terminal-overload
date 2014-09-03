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

	test -d linux32 && rm -r linux32
	test -d win32 && rm -r win32

	cp -r 'source/My Projects/main/game' linux32 || abort
	FIND_ARGS="linux32"
	for EXT in dmp psd src.png max xcf blend dae
	do
		FIND_ARGS="$FIND_ARGS -name *.$EXT -execdir rm {} ; -o"
	done
	FIND_ARGS="$FIND_ARGS -false"
	#echo "find $FIND_ARGS"
	find $FIND_ARGS
	cp -r linux32 win32 || abort

	rm linux32/*.dll || abort
	rm -r win32/lib || abort
	rm win32/overload.sh || abort
	cp ../bins/linux32/* linux32/ || abort
	cp ../bins/win32/* win32/ || abort

	chrpath -r '$ORIGIN/lib' linux32/overload
)

create_platform_dists

