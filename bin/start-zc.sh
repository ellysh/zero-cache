#!/bin/bash

./clean.sh

./zero-cache -l zero-cache.log -c "ipc:///tmp/0" -s 10000 -k 10
#./zero-cache -l zero-cache.log -c "tcp://*:5570" -s 10000 -k 10
