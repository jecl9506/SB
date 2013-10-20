#!/bin/bash

NAME="grplist.so"
COMPILER="gcc"
SOURCE="grplist.c ../../group.c ../../../Common/unix_socket.c"

# Create objects files
$COMPILER -c -fPIC $SOURCE

# Create dynamic library
$COMPILER -shared -lc -o $NAME *.o
