cmake_minimum_required(VERSION 3.13)
project(iprefresher VERSION 1.2.0 DESCRIPTION "Dynu ip refresher")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release) # manually set build type (Release / Debug)
set(libmethod STATIC) #SHARED / STATIC
set(WinBuild true)

#set up toolchain

if (${WinBuild})
    set(LIBSUFFIX .dll)
    set(SUFFIX .exe)

    set(CMAKE_SYSTEM_NAME Windows)
    set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)
    #set(TOOLCHAIN_PREFIX i686-w64-mingw32)

    # cross compilers to use for C and C++
    set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
    set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
    set(CMAKE_RC_COMPILER ${TOOLCHAIN_PREFIX}-windres)

    # target environment on the build host system
    set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX}/sys-root/mingw /usr/lib/gcc/${TOOLCHAIN_PREFIX}/8.3.0)


    # modify default behavior of FIND_XXX() commands to
    # search for headers/libs in the target environment and
    # search for programs in the build host environment
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

    #    set(CMAKE_CXX_STANDARD_LIBRARIES -lcurl -lpthread -static-libgcc -static-libstdc++ -lcrypto -lssl -lws2_32 -std=c++11 -static -DCURL_STATICLIB)
    set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++  -lcurl -lpthread -lstdc++ -lwsock32 -lws2_32 ${CMAKE_CSS_STANDARD_LIBRARIES}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -Wl,-Bstatic,--whole-archive -Wl,--no-whole-archive")
    #    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    #    set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)
    add_definitions(-DCURL_STATICLIB)
else ()
    set(LIBSUFFIX .so)
    set(SUFFIX "")
endif ()


find_package(CURL REQUIRED)
if (CURL_FOUND)
    message(STATUS "Found CURL version: ${CURL_VERSION_STRING}")
    message(STATUS "Using CURL include dir(s): ${CURL_INCLUDE_DIRS}")
    message(STATUS "Using CURL lib(s): ${CURL_LIBRARIES}")
    #        include_directories(${CURL_INCLUDE_DIRS})
else ()
    message(FATAL_ERROR "Could not find CURLLL")
endif ()
include_directories(${CURL_INCLUDE_DIR} inc)

add_library(api ${libmethod}
        src/api/API.cpp

        src/api/TelegramAPI.cpp

        src/api/DynuAPI.cpp

        src/api/IPAPI.cpp
        )

add_library(logger ${libmethod}
        src/Logger.cpp
        )


set(SOURCE
        src/main.cpp
        src/IPRefresher.cpp inc/IPRefresher.h)

add_executable(iprefresher ${SOURCE})

# LINK generated LIBS #
target_link_libraries(iprefresher api logger ${CURL_LIBRARIES})

# INSTALL to SYSTEM #
install(TARGETS iprefresher DESTINATION bin)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/iprefresher.service DESTINATION lib/systemd/system)


IF (UNIX)
    SET(CPACK_DEB_COMPONENT_INSTALL 1)

    FIND_PROGRAM(RPMBUILD_EXECUTABLE rpmbuild)
    FIND_PROGRAM(DEB_EXECUTABLE dpkg)

    SET(CPACK_GENERATOR "TGZ;TBZ2")

    #check if rpm build is possible
    if (NOT ${RPMBUILD_EXECUTABLE} STREQUAL "RPMBUILD_EXECUTABLE-NOTFOUND")
        message(STATUS "found rpm build executeable --> able to build rpm")
        set(CPACK_GENERATOR "${CPACK_GENERATOR};RPM")
        set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/usr/lib/systemd/system" "/usr/lib/systemd") # --> needed to not override existing folders
    else (NOT ${RPMBUILD_EXECUTABLE} STREQUAL "RPMBUILD_EXECUTABLE-NOTFOUND")
        message(STATUS "not found rpm build tools --> not building rpm")
    endif (NOT ${RPMBUILD_EXECUTABLE} STREQUAL "RPMBUILD_EXECUTABLE-NOTFOUND")

    #check if deb build is possible
    if (NOT ${DEB_EXECUTABLE} STREQUAL "DEB_EXECUTABLE-NOTFOUND")
        message(STATUS "found deb build tools --> able to build deb")
        set(CPACK_GENERATOR "${CPACK_GENERATOR};DEB")
    else (NOT ${DEB_EXECUTABLE} STREQUAL "DEB_EXECUTABLE-NOTFOUND")
        message(STATUS "not found  deb build tools --> not building deb")
    endif (NOT ${DEB_EXECUTABLE} STREQUAL "DEB_EXECUTABLE-NOTFOUND")


    SET(CPACK_CMAKE_GENERATOR "Unix Makefiles")
    SET(CPACK_SOURCE_GENERATOR "TGZ;TBZ2")

    SET(CPACK_PACKAGE_DESCRIPTION "IPrefresher to refresh Dynu ip address and notify user via Telegram")
    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "IPrefresher to refresh Dynu ip address and notify user via Telegram")
    SET(CPACK_PACKAGE_VENDOR "Lukas Heilgienbrunner")
    SET(CPACK_PACKAGE_VERSION_MAJOR "1")
    SET(CPACK_PACKAGE_VERSION_MINOR "2")
    SET(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
    SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION}")
    SET(CPACK_PACKAGE_CONTACT "Lukas Heiligenbrunner <ultimategameingcookie@gmail.com>")
    SET(CPACK_PACKAGE_SECTION "games")

    INCLUDE(CPack)

    add_custom_target(build-linux-packages
            "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target package
            DEPENDS ${PROJECT_NAME}
            COMMENT "Installing ${PROJECT_NAME}")

ENDIF (UNIX)