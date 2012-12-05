#!/bin/bash

./clean.sh

./zero-cache -l zero-cache.log -c "tcp://*:5570" -s 10000
#zero-cache -l zero-cache.log -c "tcp://*:5570" -s 1000
#valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes --collect-jumps=yes ./zero-cache -l zero-cache.log -c "tcp://*:5570" -s 10000
