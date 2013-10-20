#!/bin/bash

NAME="list.so"
COMPILER="gcc"
SOURCE="list.c ../../../Common/unix_socket.c"

# Create objects files
$COMPILER -c -fPIC $SOURCE

# Create dynamic library
$COMPILER -shared -lc -o $NAME *.o
