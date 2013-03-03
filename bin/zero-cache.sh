#!/bin/bash

sudo rmmod zero_cache
sudo rm -f /dev/zero_cache
sudo insmod ../source/server/zero_cache.ko
