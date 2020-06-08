[![pipeline status](http://gitlab.heili.eu/lukas/dynuiprefresher/badges/master/pipeline.svg)](http://gitlab.heili.eu/lukas/dynuiprefresher/-/commits/master)
# DynuIPRefresher
A lightweight C++ application to setup a service for refreshing a dynamic IP to the Dynu servers. 
Dynu.com is a free DDns service and provides an API.
There is also a GUI for Windows Users and beginners.

## Installation
Download the latest Release at [Release_Page](https://github.com/Lukas-Heiligenbrunner/DynuIPRefresher/releases).
I'm providing executables for Debian/Ubuntu (.deb) and RHEL/Debian (.rpm). 
But you can still compile the code my your own (see build section).

## Configuration
There is a configuration file `/etc/dynuiprefresher.cfg` where you have to specify the DYNU API key (get it from their homepage), the domainid and your domain.
Furthermore, you can optionally specify a Telegram API key and a Chat ID if you want to be notfied when your local ip changes.

To enable and start the service: 
`systemctl enable dynuiprefresher.service` and `systemctl start dynuiprefresher.service`

## Usage
First of all configure the right keys in the `/etc/dynuiprefresher.cfg` or `%appdata%\DynuIpRefresher\dynuiprefresher.cfg` config file.

Afterwards use the following options: 

```
help page: 
[-h] [--help]  print this help page
[-v] [--version] print the software version
[-f] [--force] force refresh of ip
[-l] [--loop] infinite loop to refresh ip every five minutes
[-c] [--checkconfig] validate configuration
[-ip] [--currentip] get current global ip
[no argument] normal ip check and refresh
```

### GUI 

You can also build the grapical user inteface if you want. 
There you can manually trigger a refresh in a gui and set all the config parameters.

Home Page:
![couldn't load image](https://i.ibb.co/syDwWQg/Screenshot-20200608-104253.png)

Config Page:
![couldn't load image](https://i.ibb.co/89vnJXY/Screenshot-20200608-104308.png)


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

### GUI Build

please use the predefined Docker-Image here: 
[DockerHub](https://hub.docker.com/repository/docker/luki42/dynuiprefresher_build)


### Windows cross build
Set Winbuild flag in CMakeList.txt.

Dependencies:
* MinGW Compiler
* MinGW-libcurl
* MinGW-libconfig++

Optional dependencies
* NSIS Pack tool (for creating installer)
* doxygen (for generating html doc)

The Simplest way to install all dependencies is the preconfigured Docker-Image:
[DockerHub](https://hub.docker.com/repository/docker/luki42/dynuiprefresher_build)

`make package` will pack it into a NSIS installer for Windows. 
