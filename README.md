# DynuIPRefresher

`git clone https://github.com/Lukas-Heiligenbrunner/DynuIPRefresher.git`
`mv DynuIPRefresher iprefresher`

`cd iprefresher`
`tar -zcvf iprefresher-1.0.tar.gz *`

`dh_make -f iprefresher-1.0.tar.gz`

`cd debian`
`rm *.ex *.EX README.Debian README.source `

`nano control`

`Source: iprefresher
Section: net
Priority: optional
Maintainer: Lukas Heiligenbrunner <lukas@unknown>
Build-Depends: debhelper (>= 10)
Standards-Version: 4.1.2

Package: iprefresher
Architecture: any
Depends: ${shlibs:Depends}, ${misc:Depends}
Description: a dynu.net ip refresher written in c++
 a dynu.net ip refresher written in c++`


`dpkg-buildpackage -S -us -uc `
`dpkg-buildpackage -us -uc `
