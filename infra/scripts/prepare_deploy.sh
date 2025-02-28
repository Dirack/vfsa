#!/bin/bash

if [ -d "dirack" ]
then
    rm -rf dirack
fi

mkdir dirack

cp ../../*.c ../../*.h ../../SConstruct dirack
cp -r ../../examples dirack

tar -cvf deploy.tar dirack