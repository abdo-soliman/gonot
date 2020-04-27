#!/bin/bash

cd build
bison --yacc ../src/gonot.y -d -b ../src/y
flex -o ../src/lex.yy.c ../src/gonot.l

SOURCE_CPP="$(find ../src -name *.cpp -printf '%p ')"
SOURCE_C="$(find ../src -name *.c -printf '%p ')"
SOURCE="$SOURCE_CPP $SOURCE_C"

flags="-std=c++17 -I$(pwd)/../src -o gonot"
g++ $flags $SOURCE