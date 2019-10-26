# DynuIPRefresher

## Build
## Basic Build
### Download source files

`git clone https://github.com/Lukas-Heiligenbrunner/DynuIPRefresher.git`

### install build dependencies

`libcurl`
`libcurl-devel`

Debian:
`apt install libcurl4-openssl-dev`

Fedora:
`dnf install libcurl-devel`

### cmake project
cd into downloaded files and Generate makefiles:

`cmake -S . -B build`

### compile project

`make`

[root] install it to the system

`make install`

[root] or create Linux packages

`make package`



### Windows cross build
TODO!
