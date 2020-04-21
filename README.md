# DBUG

## About

DBUG is a debugger designed for use with threading. DBUG was written by Fred
Fish, used in MySQL < 8, and adopted in this repository for general use.

## Examples

Examples can be built with CMake
For example, the factorial example steps are:

1. `cd` into your build directory
2. `cmake <root>`, where `<root>` is the directory with this CMakeLists.txt in it
3. `make factorial` (or your own Makefile you specified)
4. `./factorial` (or .exe etc.)
