#!/bin/bash
#
# Generate current release message based on active develop branch name

CURRENTVERSION=$(git branch | grep develop | cut -d"/" -f2)
LATESTVERSION=$(git describe --abbrev=0)
GITLOG=$(git log "$LATESTVERSION...develop/$CURRENTVERSION" --oneline)

echo "$CURRENTVERSION - [Summary]"
echo "[Description]"

echo "## Added"
echo $(echo "$GITLOG" | grep "^(feat|test)")

echo "## Changed"
echo $(echo "$GITLOG" | grep "^(perf|docs)")

echo "## Fixed"
echo $(echo "$GITLOG" | grep "^(fix)")

echo "## Removed"
echo $(echo "$GITLOG" | grep "^(revert)")

echo "## Development"
echo $(echo "$GITLOG" | grep "^(build|chore|refactor|style)")

echo "Try it on a docker container!"
echo "- Not available"
