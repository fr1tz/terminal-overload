#!/bin/sh

THIS="$0"

cd "$(dirname "$THIS")" && ./engine -dedicated -game serverlist | {
	grep '#server ' | sed 's/#server //g'
}
