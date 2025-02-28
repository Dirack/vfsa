#!/bin/bash

if [ ! -d "build" ]
then
    mkdir build
fi

echo deploy >> build/file.txt

tar -cvf deploy.tar build/*