#!/bin/bash

sudo rmmod zero-cache
sudo insmod ../source/server/zero_cache.ko
sudo rm -f /dev/zero-cache
sudo mknod /dev/zero-cache c 250 0
