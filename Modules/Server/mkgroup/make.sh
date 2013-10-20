#!/bin/bash

NAME="mkgroup.so"
COMPILER="gcc"
SOURCE="mkgroup.c ../../group.c ../../../Common/unix_socket.c"

# Create objects files
$COMPILER -c -fPIC $SOURCE

# Create dynamic library
$COMPILER -shared -lc -o $NAME *.o
