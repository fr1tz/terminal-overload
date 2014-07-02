#!/bin/sh

abort()
{
	echo "$*" 2>&1
	echo "Aborting!" 2>&1
	exit 1
}

create_packages()
(
	echo "Creating packages..."
	GAME_VERSION=$(cat dists/version)
	echo "Version string: $GAME_VERSION"
	cd packages/ || abort
	
	SOURCE_DIST_NAME="terminal-overload-$GAME_VERSION-source"
	LINUX_DIST_NAME="terminal-overload-$GAME_VERSION-linux"
	WIN32_DIST_NAME="terminal-overload-$GAME_VERSION-win32"

	test -e $SOURCE_DIST_NAME && rm -r $SOURCE_DIST_NAME
	test -e $LINUX_DIST_NAME && rm -r $LINUX_DIST_NAME
	test -e $WIN32_DIST_NAME && rm -r $WIN32_DIST_NAME

	mv ../dists/source $SOURCE_DIST_NAME || abort
	mv ../dists/linux $LINUX_DIST_NAME || abort
	mv ../dists/win32 $WIN32_DIST_NAME || abort

	tar -czf $SOURCE_DIST_NAME.tar.gz $SOURCE_DIST_NAME
	tar -czf $LINUX_DIST_NAME.tar.gz $LINUX_DIST_NAME
	zip -r $WIN32_DIST_NAME.zip $WIN32_DIST_NAME

	echo 'Done creating packages!'
)

for CMD in cat tar zip
do
	which $CMD || abort "Required command not found: $CMD"
done

for DIR in dists/source dists/linux dists/win32 packages
do
	test -d $DIR || abort "$DIR not found."
done

create_packages
