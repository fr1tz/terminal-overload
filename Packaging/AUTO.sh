#!/bin/sh

./init.sh &&
./create_source_dist.sh &&
./strip_source_dist.sh &&
./create_platform_dists.sh &&
./create_packages.sh
