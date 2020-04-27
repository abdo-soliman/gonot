#!/bin/bash

cd build
bison --yacc ../src/grammar/gonot.y -d -b ../src/grammar/y
flex -o ../src/grammar/lex.yy.c ../src/grammar/gonot.l

SOURCE_CPP="$(find ../src -name *.cpp -printf '%p ')"
SOURCE_C="$(find ../src -name *.c -printf '%p ')"
SOURCE="$SOURCE_CPP $SOURCE_C"

flags="-std=c++17 -I$(pwd)/../src -o gonot"
g++ $flags $SOURCE
