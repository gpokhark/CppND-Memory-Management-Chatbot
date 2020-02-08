#!/bin/bash
# Script to check for memory leaks
#

# valgrind
cd ./build/
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=log.txt ./membot
cd ..
code -n ./build/log.txt
