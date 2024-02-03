#!/bin/bash
#
# Generate current release message based on active develop branch name

CURRENTVERSION=$(git branch | grep develop | cut -d"/" -f2)
LATESTVERSION=$(git describe --abbrev=0)
GITLOG=$(git log "$LATESTVERSION...develop/$CURRENTVERSION" --oneline)
GITLOG=$(git log "$LATESTVERSION...master" --oneline)

echo "$CURRENTVERSION - [Summary]"
echo ""
echo "[Description]"
echo ""

echo "## Added"
echo "$(echo "$GITLOG" | grep -E "^\[(feat|test)\]" | sed 's/^/- /')"
echo ""

echo "## Changed"
echo "$(echo "$GITLOG" | grep -E "^\[(perf|docs)\]" | sed 's/^/- /')"
echo ""

echo "## Fixed"
echo "$(echo "$GITLOG" | grep -E "^\[(fix)\]" | sed 's/^/- /')"
echo ""

echo "## Removed"
echo "$(echo "$GITLOG" | grep -E "^\[(revert)\]" | sed 's/^/- /')"
echo ""

echo "## Development"
echo "$(echo "$GITLOG" | grep -E "\[(build|chore|refactor|style)\]" | sed 's/^/- /')"
echo ""

echo "## Try it on a docker container!"
echo ""
echo "From root directory of this repository run to build the image:"
echo "\`\`\`sh"
echo "docker build -t vfsa:${CURRENTVERSION} -f ./infra/docker/Dockerfile ."
echo "\`\`\`sh"
echo ""

echo "To run it on a docker container use:"
echo "\`\`\`sh"
echo "docker run -ti vfsa:${CURRENTVERSION}"
echo "\`\`\`sh"
