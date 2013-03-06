#!/bin/bash

rm -f *.log

for (( i=0; i<=50; i++ ))
do
    rm $i
done

rm -f /var/run/zero-cache/*
