#!/bin/sh

abort()
{
	echo "$*" 2>&1
	echo "Aborting!" 2>&1
	exit 1
}

create_source_dist()
(
	echo "Creating source distribution..."
	cd dists/ || abort

	test -e source && rm -r source

	echo "Creating master .zip..."
	( cd ../../ && git archive -o Packaging/dists/master.zip HEAD ) || abort
	echo "Creating source dist file tree..."
	( mkdir source && cd source && unzip ../master.zip ) || abort
	echo "Removing master .zip..."
	rm master.zip || abort
)

create_source_dist
