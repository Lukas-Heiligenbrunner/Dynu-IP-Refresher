# DynuIPRefresher
A lightweight C++ application to setup a service for refreshing a dynamic IP to the Dynu servers. 
Dynu.com is a free DDns service and provides an API.

## Installation
Download the latest Release at [Release_Page](https://github.com/Lukas-Heiligenbrunner/DynuIPRefresher/releases).
I'm providing executables for Debian/Ubuntu (.deb) and RHEL/Debian (.rpm). 
But you can still compile the code my your own (see build section).

## Configuration
There is a configuration file `/etc/iprefresher.cfg` where you have to specify the DYNU API key (get it from their homepage), the domainid and your domain.
Furthermore, you can optionally specify a Telegram API key and a Chat ID if you want to be notfied when your local ip changes.


## Build
## Basic Build
### Download source files

`git clone https://github.com/Lukas-Heiligenbrunner/DynuIPRefresher.git`

### install build dependencies

`libcurl`
`libconfig`

#### Debian:
`apt install libcurl4-openssl-dev`

#### Fedora:
`dnf install libcurl-devel libconfig-devel`

#### Alpine Linux:
Compiler dependencies:

`apk add make cmake g++`

Lib dependencies:

`apk add libcurl curl-dev libconfig libconfig-dev`

Packaging dependencies:

`apk add dpkg rpm`


#### dependencies for package build
`dpkg` --> debian/ubuntu package

`rpmbuild` --> Fedora/RedHat/CentOS package

### cmake project
cd into downloaded files and Generate makefiles:

`cmake -S . -B build`

### compile project

`make`

[root] install it to the system

`make install`

(optional) create Linux packages

`make package`



### Windows cross build
TODO!
