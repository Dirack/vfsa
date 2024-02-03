#!/bin/bash
#
# Check current version based on active develop branch name

VERSIONDOC=$(cat docs/VERSION.md)
CURRENTVERSION=$(git branch -a)

if [ "$VERSIONDOC" != "$CURRENTVERSION"	]; then
	echo "Package version in VERSION.md file does not seem correct!"
	echo "Version from VERSION.md file: $VERSIONDOC"
	echo "Version extracted from active develp branch name: $CURRENTVERSION"
	exit 1
fi
