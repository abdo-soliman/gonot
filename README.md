# gonot
A compiler for Gonot Langauge

## Dependencies
This Project depends on the following tools:
1. [GNU g++](https://gcc.gnu.org/) 7.5.0 or later
2. [GNU bison](https://www.gnu.org/software/bison/)
3. [GNU flex](https://github.com/westes/flex/)

## Build
To build the project run the following command
```bash
mkdir build
chmod +x build.sh
./build.sh
```

## Run
After building gonot compiler you will find a binary file in the build directory with the name **gonot** to compile gonot application use the following command
```bash
./gonot [/path/to/source/file]
```
