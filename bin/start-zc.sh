#!/bin/bash

./clean.sh

sudo rmmod zero-cache
sudo insmod ../source/server/zero-cache.ko
sudo rm -f /dev/zero-cache
sudo mknod /dev/zero-cache c 251 0
