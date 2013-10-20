#!/bin/bash

NAME="exec.so"
COMPILER="gcc"
SOURCE="exec.c ../../cqueue.c"

# Create objects files
$COMPILER -c -fPIC $SOURCE

# Create dynamic library
$COMPILER -shared -lc -o $NAME *.o
