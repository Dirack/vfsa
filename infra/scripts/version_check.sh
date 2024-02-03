#!/bin/bash
#
# Check current version based on active develop branch name


VERSIONDOC=$(cat docs/VERSION.md)

if git fetch origin "develop/$VERSIONDOC"; then
	echo "Version checked: $VERSIONDOC"
	exit 0
else
	echo "Package version in VERSION.md file does not seem correct!"
	echo "Version from VERSION.md file: $VERSIONDOC"
	exit 1
fi
