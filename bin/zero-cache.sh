#!/bin/bash

sudo rmmod zero_cache
sudo insmod ../source/server/zero_cache.ko
sudo rm -f /dev/zero_cache
sudo mknod /dev/zero_cache c 250 0
