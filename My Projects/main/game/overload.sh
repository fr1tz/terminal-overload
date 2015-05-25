#!/bin/sh

help_reminder()
{
	echo
	echo "Reminder: If you're stuck and need help, visit the Terminal Overload forum:"
	echo "            http://forum.freegamedev.net/viewforum.php?f=87"
	echo
}

check_lib()
{
	lib="$1"
	echo "Checking for 32 bit version of $lib..."
	tokens="$(ldconfig -p | grep "$lib")"
	for token in $tokens
	do
		test -f $token || continue
		(objdump -x "$token" | grep -q elf32-i386) && {
			echo " -> $token"
			return 0
		}
	done	
	echo "   !!! Unable to find 32 bit version of $lib !!!"
	MISSING_LIBS="$MISSING_LIBS $lib"
	return 1
}

THIS="$0"
GAME_ARGS="$*"
PATHBAK="$PATH"

echo "--------------------------------"
echo "Terminal Overload Startup Script"
echo "--------------------------------"
echo

# On some systems these are not part of the user's default $PATH
PATH="/sbin:/usr/sbin:$PATH" 

CMDS="readlink dirname grep ldconfig objdump test"
echo "Checking for commands required by this script..."
for CMD in $CMDS
do
	which $CMD || {
		echo "Required command $CMD not available!"
		echo "Please make sure the following commands are available:"
		for CMD in $CMDS
		do
			echo "   - $CMD"
		done
		help_reminder
		exit 1
	}
done

LIBS="libGL.so.1"
MISSING_LIBS=""
echo
echo "Checking for libraries required to run Terminal Overload..."
for LIB in $LIBS
do
	check_lib $LIB
done

test "x$MISSING_LIBS" = "x" || {
	echo
	echo "Unable to locate 32 bit versions of the following libraries:"
	for MISSING_LIB in $MISSING_LIBS
	do
		echo "   - $MISSING_LIB"
	done
	echo
	echo "Please install 32 bit versions of the missing libraries and try again."
	help_reminder	
	exit 1
}

PATH="$PATHBAK"
GAME_DIR="$(dirname "$(readlink -f "$THIS")")"
echo
echo "Game directory:" "$GAME_DIR"
echo "Starting game..."

export LD_LIBRARY_PATH="$GAME_DIR/lib:$LD_LIBRARY_PATH" &&
cd "$GAME_DIR" && ./lib/ld-linux.so.2 ./overload $GAME_ARGS || help_reminder
