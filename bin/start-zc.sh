#!/bin/bash

./clean.sh

./zero-cache -l zero-cache.log -c "tcp://*:5570" -s 1000
