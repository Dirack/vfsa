#!/bin/bash

if [ -d "dirack" ]
then
    rm -rf dirack
fi

mkdir dirack

cp ../../*.c ../../*.h ../../SConstruct dirack

tar -cvf deploy.tar dirack