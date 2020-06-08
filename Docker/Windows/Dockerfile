FROM fedora:33
MAINTAINER luki42

RUN \
    \
    # Install texlive
    echo "instaling cmake" && \
    dnf install -y mingw64-gcc-c++ mingw64-curl-static mingw64-qt5-qtbase wget cmake make tar xz mingw32-nsis gtest gtest-devel && \
    wget http://repo.msys2.org/mingw/x86_64/mingw-w64-x86_64-libconfig-1.7.2-1-any.pkg.tar.xz && \
    tar -xf mingw-w64-x86_64-libconfig-1.7.2-1-any.pkg.tar.xz && \
    mv ./mingw64/bin/* /usr/x86_64-w64-mingw32/sys-root/mingw/bin && \
    mv ./mingw64/include/* /usr/x86_64-w64-mingw32/sys-root/mingw/include && \
    mv ./mingw64/lib/*.a /usr/x86_64-w64-mingw32/sys-root/mingw/lib && \
    mv ./mingw64/lib/cmake/* /usr/x86_64-w64-mingw32/sys-root/mingw/lib/cmake && \
    rm -Rv mingw-w64-x86_64-libconfig-1.7.2-1-any.pkg.tar.xz mingw64 && \
    #cleanup
    dnf clean dbcache && dnf clean packages
# Expose /home as workin dir
WORKDIR /home
VOLUME ["/home"]