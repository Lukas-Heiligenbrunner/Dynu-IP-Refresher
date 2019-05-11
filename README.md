# DynuIPRefresher

## Build
## Basic Build
Download source files

`git clone https://github.com/Lukas-Heiligenbrunner/DynuIPRefresher.git`

cd into downloaded files and Generate makefiles:

`cmake .`

compile project

`make`

install it to the system

`make install`

### Build a Debian package
Download source files

`git clone https://github.com/Lukas-Heiligenbrunner/DynuIPRefresher.git`

rename Project folder to lower case:

`mv DynuIPRefresher iprefresher-1.0`

`cd iprefresher-1.0`

remove .idea folder because it´s useless in this case:

`rm -Rf .idea`

pack source in a tar.gz archive

`tar -zcvf iprefresher-1.0.tar.gz *`

create debian/ folder and create example config files

`dh_make -f iprefresher-1.0.tar.gz`

recently packed archive is useless now, delete it

`rm iprefresher-1.0.tar.gz`

move to debian/ folder:

`cd debian`

remove useless files:

`rm *.ex *.EX README.Debian README.source `

edit control file

`rm control`

`nano control`

```
Source: iprefresher
Section: net
Priority: optional
Maintainer: Lukas Heiligenbrunner <lukas@unknown>
Build-Depends: debhelper (>= 10)
Standards-Version: 4.1.2

Package: iprefresher
Architecture: any
Depends: ${shlibs:Depends}, ${misc:Depends}
Description: a dynu.net ip refresher written in c++
 a dynu.net ip refresher written in c++
```
return to main folder

`cd ..`

buld .deb package

`dpkg-buildpackage -us -uc `

### Windows cross build
TODO!
