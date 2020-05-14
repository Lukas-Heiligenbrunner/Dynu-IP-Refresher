# @author Lukas Heiligenbrunner
# main CMake file
#
# Build lib dependencies:
## libcurl (with sources)
## libconfig (with sources)
#
# for documenation build doxygen needs to be installed.
# for test build gtest needs to be installed.

cmake_minimum_required(VERSION 3.13)
project(iprefresher DESCRIPTION "Dynu ip refresher")
SET(PROJECT_VERSION 1.3.3)

# CONFIGURATION
SET(CMAKE_BUILD_TYPE Release) # manually SET build type (Release / Debug)
SET(LIB_METHOD STATIC) #SHARED / STATIC

option(BUILD_DOC "Build documentation" ON) # additional dependency for Doxygen
option(PACKAGING "Allow Packaging to <exe>, <deb> or <rpm>" ON) # additional dependencies for RPMbuild,dpkg  or NSIS
option(TESTS "Build Tests" ON) # additional dependencies for GTEST - to build tests
option(GUI "Build GUI elements" ON) # additional dependencies to QT libraries needed
set(WinBuild false)

# helper variables
SET(CMAKE_CXX_STANDARD 17)
string(TIMESTAMP TIMESTAMP_NOW "%d.%m.%Y")

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# setup winbuild compilers
if (${WinBuild})
    set(LIBSUFFIX .dll)
    set(SUFFIX .exe)

    set(CMAKE_SYSTEM_NAME WindowsStore)
    set(CMAKE_SYSTEM_VERSION 10.0)
    set(TOOLCHAIN_PREFIX x86_64-w64-mingw32) # x64 build toolchain
    #set(TOOLCHAIN_PREFIX i686-w64-mingw32)

    # cross compilers to use for C and C++
    set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
    set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
    set(CMAKE_RC_COMPILER ${TOOLCHAIN_PREFIX}-windres)

    # target environment on the build host system
    set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})


    # modify default behavior of FIND_XXX() commands to
    # search for headers/libs in the target environment and
    # search for programs in the build host environment
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

    set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CSS_STANDARD_LIBRARIES}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
    # currently libs are dynamically linked eg. dlls have to be copied to same folder
    # todo link dynamically.
    # maybe so: set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")
    # or set(CMAKE_CXX_STANDARD_LIBRARIES -lcurl -lpthread -static-libgcc -static-libstdc++ -lcrypto -lssl -lws2_32 -static -DCURL_STATICLIB)
    # or add_definitions(-DCURL_STATICLIB)

    # windows config path is same as executable
    set(CONFIG_PATH "./iprefresher.cfg")
else ()
    set(LIBSUFFIX .so)
    set(SUFFIX "")

    # set /etc/ config path
    set(CONFIG_PATH "/etc/iprefresher.cfg")
endif ()


# config libs
message(STATUS "Config of Libraries")
# libcurl
if (${WinBuild})
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".dll")
    # configure libcurl
    FIND_PATH(CURL_INCLUDE_DIRS curl/curl.h /usr/${TOOLCHAIN_PREFIX}/sys-root/mingw/include/) # search for libconfig include headers
    FIND_LIBRARY(CURL_LIBRARIES NAMES libcurl.dll.a HINTS /usr/${TOOLCHAIN_PREFIX}/sys-root/mingw/lib) # search for actual lib

    message(STATUS "Using CURL include dir(s): ${CURL_INCLUDE_DIRS}")
    message(STATUS "Using CURL lib(s): ${CURL_LIBRARIES}")
    message(STATUS "")

    include_directories(${CURL_INCLUDE_DIRS} inc)

    # configure libconfig
    FIND_PATH(LIBCONFIG++_INCLUDE_DIRS libconfig.h++ /usr/${TOOLCHAIN_PREFIX}/sys-root/mingw/include/) # search for libconfig include headers
    FIND_LIBRARY(LIBCONFIG++_LIBRARIES NAMES libconfig++.dll.a HINTS /usr/${TOOLCHAIN_PREFIX}/sys-root/mingw/lib) # search for actual lib

    message(STATUS "Using LIBCONFIG++ include dir(s): ${LIBCONFIG++_INCLUDE_DIRS}")
    message(STATUS "Using LIBCONFIG++ lib(s): ${LIBCONFIG++_LIBRARIES}")

    include_directories(${LIBCONFIG++_INCLUDE_DIRS} inc)

    if (${GUI})
        set(CMAKE_PREFIX_PATH "/usr/${TOOLCHAIN_PREFIX}/sys-root/mingw/lib/cmake")
    endif ()
else ()
    find_package(CURL REQUIRED)
    if (CURL_INCLUDE_DIRS AND CURL_LIBRARIES)
        message(STATUS "Found CURL version: ${CURL_VERSION_STRING}")
        message(STATUS "Using CURL include dir(s): ${CURL_INCLUDE_DIRS}")
        message(STATUS "Using CURL lib(s): ${CURL_LIBRARIES}")
    else ()
        message(FATAL_ERROR "Could not find CURL")
    endif ()
    include_directories(${CURL_INCLUDE_DIR} inc)

    message("")
    # libconfig
    FIND_PATH(LIBCONFIG++_INCLUDE_DIRS
            NAMES libconfig.h++
            PATHS /usr/include /usr/local/include) # search for libconfig include headers
    FIND_LIBRARY(LIBCONFIG++_LIBRARIES
            NAMES config++
            PATHS /usr/lib /usr/local/lib) # search for actual lib

    if (LIBCONFIG++_INCLUDE_DIRS AND LIBCONFIG++_LIBRARIES)
        message(STATUS "Fount libconfig!")
        message(STATUS "Using libconfig include dir(s): ${LIBCONFIG++_INCLUDE_DIRS}")
        message(STATUS "Using libconfig lib(s): ${LIBCONFIG++_LIBRARIES}")
    else ()
        message(FATAL_ERROR "Could not find LIBCONFIG")
    endif ()

    include_directories(${LIBCONFIG_INCLUDE_DIRS})
endif ()

if (${GUI})
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)

    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5PrintSupport REQUIRED)
    find_package(Qt5Sql REQUIRED)
endif ()

message("")

#read sample config
FILE(READ ${CMAKE_SOURCE_DIR}/config/iprefresher.cfg SAMPLECONFIG)
#add version header
FILE(WRITE ${CMAKE_SOURCE_DIR}/inc/Version.h
        "/**
 * Version header to store Version, Config dir and a Sample config
 * Do not edit this file manually, it is generated by the cmake script!
 *
 * @author Lukas Heiligenbrunner
 * @date ${TIMESTAMP_NOW}
 */

#pragma once

#include <string>

namespace Version {
  const std::string VERSION = \"${PROJECT_VERSION}\";
  const std::string ConfigDir = \"${CONFIG_PATH}\";
  const std::string SAMPLECONFIG = R\"(${SAMPLECONFIG})\";
}"
        )

add_library(api ${LIB_METHOD}
        src/api/API.cpp
        src/api/TelegramAPI.cpp
        src/api/DynuAPI.cpp
        src/api/IPAPI.cpp)

add_library(dynuiprefresher ${LIB_METHOD}
        src/IPRefresher.cpp
        src/Config.cpp
        src/IpHelper.cpp
        src/FileLogger.cpp
        src/Logger.cpp
        )

add_executable(iprefresher src/main.cpp)

# LINK generated LIBS #
target_link_libraries(iprefresher dynuiprefresher api ${CURL_LIBRARIES} ${LIBCONFIG++_LIBRARIES})

if (${GUI})
    set(QT5_LIBRARIES Qt5::Widgets Qt5::PrintSupport Qt5::Sql)

    set(UI_SOURCES
            src/gui/mainwindow.ui
            )

    #
    # Generate necessary headers from .ui files. (qmake lets `uic` do this job.)
    # hint from [Cross-platform Qt5 project using cmake](http://stackoverflow.com/questions/21174586/cross-platform-qt5-project-using-cmake)
    #
    qt5_wrap_ui(UI_GENERATED_HEADERS ${UI_SOURCES})

    add_executable(iprefresher-gui
            src/maingui.cpp
            src/gui/MainWindow.cpp
            src/gui/MainWindow.h ${UI_GENERATED_HEADERS})

    # LINK generated LIBS #
    target_link_libraries(iprefresher-gui -lpthread dynuiprefresher api ${CURL_LIBRARIES} ${LIBCONFIG++_LIBRARIES} ${QT5_LIBRARIES})
endif ()

# setting install targets
IF (NOT ${WinBuild})
    # INSTALL to Linux SYSTEM #

    # install binaries
    install(TARGETS iprefresher DESTINATION usr/bin)
    # install systemd service and enable it
    install(FILES service/iprefresher.service DESTINATION lib/systemd/system)
ELSE ()
    # INSTALL to Windows SYSTEM #

    # install binary to current folder
    set_target_properties(iprefresher PROPERTIES SUFFIX ".exe")
    install(TARGETS iprefresher DESTINATION .)

    # install .dll dependencies
    # todo check if files exist...
    install(FILES /usr/${TOOLCHAIN_PREFIX}/sys-root/mingw/bin/libcurl-4.dll
            /usr/${TOOLCHAIN_PREFIX}/sys-root/mingw/bin/libssh2-1.dll
            /usr/${TOOLCHAIN_PREFIX}/sys-root/mingw/bin/libstdc++-6.dll
            /usr/${TOOLCHAIN_PREFIX}/sys-root/mingw/bin/libgcc_s_seh-1.dll
            /usr/${TOOLCHAIN_PREFIX}/sys-root/mingw/bin/libcrypto-1_1-x64.dll
            /usr/${TOOLCHAIN_PREFIX}/sys-root/mingw/bin/libssl-1_1-x64.dll
            /usr/${TOOLCHAIN_PREFIX}/sys-root/mingw/bin/libwinpthread-1.dll
            /usr/${TOOLCHAIN_PREFIX}/sys-root/mingw/bin/zlib1.dll
            /usr/${TOOLCHAIN_PREFIX}/sys-root/mingw/bin/libidn2-0.dll
            /usr/${TOOLCHAIN_PREFIX}/sys-root/mingw/bin/libconfig++-11.dll
            DESTINATION .)
ENDIF ()

if (${PACKAGING})
    # General Packaging options:
    message(STATUS "config of Package build")

    set(CPACK_PACKAGE_NAME "DynuIpRefresher")
    SET(CPACK_PACKAGE_DESCRIPTION "IPrefresher to refresh Dynu ip address and notify user via Telegram")
    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "IPrefresher to refresh Dynu ip address and notify user via Telegram")
    SET(CPACK_PACKAGE_VENDOR "Lukas Heilgienbrunner")
    SET(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
    SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${PROJECT_VERSION}")
    SET(CPACK_PACKAGE_CONTACT "Lukas Heiligenbrunner <lukas.heiligenbrunner@gmail.com>")

    SET(CMAKE_INSTALL_PREFIX "/")

    IF (NOT ${WinBuild})
        # generate post script for checking if configuration already exists
        FILE(WRITE ${CMAKE_SOURCE_DIR}/postinst
                "#!/bin/bash
# Post installation script for linux packages
# do not edit this file manually, it is generated by the cmake script
if [ ! -f ${CONFIG_PATH} ]; then
    cat > ${CONFIG_PATH} <<- EOM
${SAMPLECONFIG}EOM
fi\n"
                )


        SET(CPACK_DEB_COMPONENT_INSTALL 1)
        SET(CPACK_OUTPUT_FILE_PREFIX packages)
        SET(CPACK_PACKAGING_INSTALL_PREFIX "/") # no prefix for package structure

        FIND_PROGRAM(RPMBUILD_EXECUTABLE rpmbuild)
        FIND_PROGRAM(DEB_EXECUTABLE dpkg)

        SET(CPACK_GENERATOR "TGZ;TBZ2")

        #check if rpm build is possible
        if (NOT ${RPMBUILD_EXECUTABLE} STREQUAL "RPMBUILD_EXECUTABLE-NOTFOUND")
            message(STATUS "found rpm build executeable --> able to build rpm")
            SET(CPACK_GENERATOR "${CPACK_GENERATOR};RPM")
            SET(CPACK_RPM_POST_INSTALL_SCRIPT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/postinst")
            SET(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/lib/systemd/system" "/lib/systemd" "/lib" "/usr/local/bin" "/usr/local") # --> needed to not override existing folders
            set(CPACK_RPM_PACKAGE_REQUIRES "libcurl,libconfig")
        else (NOT ${RPMBUILD_EXECUTABLE} STREQUAL "RPMBUILD_EXECUTABLE-NOTFOUND")
            message(STATUS "not found rpm build tools --> not building rpm")
        endif (NOT ${RPMBUILD_EXECUTABLE} STREQUAL "RPMBUILD_EXECUTABLE-NOTFOUND")

        #check if deb build is possible
        if (NOT ${DEB_EXECUTABLE} STREQUAL "DEB_EXECUTABLE-NOTFOUND")
            message(STATUS "found deb build tools --> able to build deb")
            SET(CPACK_GENERATOR "${CPACK_GENERATOR};DEB") # add deb generator
            set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/postinst") # set post inst file
            set(CPACK_DEBIAN_PACKAGE_DEPENDS "libcurl4,libconfig++9v5") # add debian dependencies
        else (NOT ${DEB_EXECUTABLE} STREQUAL "DEB_EXECUTABLE-NOTFOUND")
            message(STATUS "not found  deb build tools --> not building deb")
        endif (NOT ${DEB_EXECUTABLE} STREQUAL "DEB_EXECUTABLE-NOTFOUND")


        SET(CPACK_CMAKE_GENERATOR "Unix Makefiles")
        SET(CPACK_SOURCE_GENERATOR "TGZ;TBZ2")

        SET(CPACK_PACKAGE_SECTION "games")
    ELSE ()
        # Pack a NSIS intaller
        set(CPACK_GENERATOR NSIS)
        message(STATUS "Using NSIS Package build.")

        set(CPACK_NSIS_testcomp_INSTALL_DIRECTORY /)
        set(CPACK_PACKAGE_INSTALL_DIRECTORY "DynuIpRefresher")
        SET(CPACK_NSIS_MODIFY_PATH ON)
    ENDIF ()

    INCLUDE(CPack)

    add_custom_target(build-packages
            "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target package
            DEPENDS ${PROJECT_NAME}
            COMMENT "Packing ${PROJECT_NAME}")
    message("")
ENDIF ()

# check if Doxygen is installed
if (BUILD_DOC)
    message(STATUS "config of DOxygen build")
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        # SET input and output files
        SET(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        SET(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        # request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

        # note the option ALL which allows to build the docs together with the application
        add_custom_target(doc_doxygen ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM)
        message(STATUS "Successfully configured doxygen")
    else (DOXYGEN_FOUND)
        message(STATUS "Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
    message("")
endif (BUILD_DOC)

# Test Cases
if (TESTS)
    include(GoogleTest)

    mark_as_advanced(
            BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
            gmock_build_tests gtest_build_samples gtest_build_tests
            gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
    )

    enable_testing()

    macro(package_add_test TESTNAME)
        # create an exectuable in which the tests will be stored
        add_executable(${TESTNAME} ${ARGN})
        # link the Google test infrastructure, mocking library, and a default main fuction to
        target_link_libraries(${TESTNAME} gtest gtest_main -lpthread -lm dynuiprefresher api ${CURL_LIBRARIES} ${LIBCONFIG++_LIBRARIES})
        # see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html for more options to pass to it
        gtest_discover_tests(${TESTNAME}
                WORKING_DIRECTORY ${PROJECT_DIR}
                EXTRA_ARGS --gtest_output=xml:report.xml -VV
                PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
                )
        set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
    endmacro()

    package_add_test(test1 tests/UnitTest.cpp ${SOURCE})

    add_custom_target(build-test
            "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target test
            DEPENDS ${PROJECT_NAME}
            COMMENT "Packing ${PROJECT_NAME}")

    add_custom_target(build-xml
            "bin/test1" --gtest_output="xml:report.xml"
            DEPENDS ${PROJECT_NAME}
            COMMENT "Packing ${PROJECT_NAME}")
ENDIF ()