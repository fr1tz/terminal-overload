#!/bin/sh

abort()
{
	echo "$*" 2>&1
	echo "Aborting!" 2>&1
	exit 1
}

print_game_version_string()
{
	cut -d '"' -f 2 < '../My Projects/main/game/version.cs'
}

create_source_dist()
(
	echo "Creating master .zip..."
	( cd ../../ && git archive -o Packaging/work/master.zip HEAD ) || abort
	echo "Creating source dist file tree..."
	( mkdir source && cd source && unzip ../master.zip ) || abort
	echo "Removing master .zip..."
	rm master.zip || abort

	echo "Stripping content not included in release from source dist..."
	cd 'source/My Projects/main/game/' || abort
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

create_platform_dists()
(
	cp -r 'source/My Projects/main/game' linux
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
	cp ../../bins/linux/* linux/ || abort
	cp ../../bins/win32/* win32/ || abort

	mv source terminal-overload-$GAME_VERSION-source || abort
	mv linux terminal-overload-$GAME_VERSION-linux || abort
	mv win32 terminal-overload-$GAME_VERSION-win32 || abort
)

create_dists()
(
	echo "Creating dists..."
	cd dists/ || abort
	create_source_dist || abort	
	create_platform_dists || abort	
)

create_packages()
(
	echo "wee"
)

for CMD in git unzip find dirname
do
	which $CMD || abort "Required command not found: $CMD"
done

test -d bins || abort "bins/ not found."
test -d dists || abort "dists/ not found."
test -d packages || abort "packages/ not found."
test -f bins/overload || abort "bins/overload is missing."
test -f bins/overload.exe || abort "bins/overload.exe is missing."

echo "Cleaning work/ directory..."
rm -r work/*

GAME_VERSION=$(print_game_version_string)
echo "Version string: $GAME_VERSION"

create_dists || abort
create_packages || abort

echo 'Done!'
