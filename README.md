# Aqua (libaqua) - A lightweight C Library
Aqua aims to be a lightweight general C library.

* Has safe and fast string functions
* application/x-www-form-urlencoded parsing
* SQL query parameterization
* Cross-platform: so far it works on Linux and Windows

## Setup
### Unix
    make
    sudo make install
### Windows
    nmake win

## See Examples

* examples/string
* examples/wc

## Testing
### Unix
    cd test
    make
    make run
### Windows
    cd Debug
    AquaTest

## License
GNU Lesser General Public License
