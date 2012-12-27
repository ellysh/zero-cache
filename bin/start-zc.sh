#!/bin/bash

RUN_DIR="/var/run/zero-cache"

if [ ! -d "$RUN_DIR" ]
then
    sudo mkdir -p "$RUN_DIR"
    sudo chmod 777 "$RUN_DIR"
fi

./clean.sh

#./zero-cache -l zero-cache.log -c "ipc:///var/run/zero-cache/0" -s 10000 -k 10
./zero-cache -l zero-cache.log -c "tcp://*:5570" -s 10000 -k 10
