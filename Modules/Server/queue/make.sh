#!/bin/bash

NAME="queue.so"
COMPILER="gcc"
SOURCE="queue.c ../../../Common/unix_socket.c"

# Create objects files
$COMPILER -c -fPIC $SOURCE

# Create dynamic library
$COMPILER -shared -lc -o $NAME *.o
