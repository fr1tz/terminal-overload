#!/bin/sh

abort()
{
	echo "$*" 2>&1
	echo "Aborting!" 2>&1
	exit 1
}

print_game_version_string()
{
	grep 'GameVersionString' '../My Projects/main/game/version.cs' | cut -d '"' -f 2 
}

echo "Cleaning work/ directory..."
rm -r dists/*

GAME_VERSION=$(print_game_version_string)
echo "Version string: $GAME_VERSION"
echo $GAME_VERSION > dists/version || abort
