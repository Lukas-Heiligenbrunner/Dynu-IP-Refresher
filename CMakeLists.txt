# author Lukas Heiligenbrunner
# main CMake file
#
cmake_minimum_required(VERSION 3.13)
project(iprefresher DESCRIPTION "Dynu ip refresher")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release) # manually set build type (Release / Debug)
set(LIB_METHOD STATIC) #SHARED / STATIC
set(PROJECT_VERSION 1.3.1)
option(BUILD_DOC "Build documentation" ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# config libs
message(STATUS "Config of Libraries")
# libcurl
find_package(CURL REQUIRED)
if (CURL_FOUND)
    message(STATUS "Found CURL version: ${CURL_VERSION_STRING}")
    message(STATUS "Using CURL include dir(s): ${CURL_INCLUDE_DIRS}")
    message(STATUS "Using CURL lib(s): ${CURL_LIBRARIES}")
else ()
    message(FATAL_ERROR "Could not find CURL")
endif ()
include_directories(${CURL_INCLUDE_DIR} inc)

# libconfig
FIND_PATH(LIBCONFIG_INCLUDE_DIR libconfig.h++ /usr/include /usr/local/include) # search for libconfig include headers
FIND_LIBRARY(CONFIG++_LIBRARY NAMES config++ PATH /usr/lib /usr/local/lib) # search for actual lib

IF (CONFIG++_LIBRARY AND LIBCONFIG_INCLUDE_DIR)
    MESSAGE(STATUS "Found Config++: ${CONFIG++_LIBRARY}")
ELSE (CONFIG++_LIBRARY AND LIBCONFIG_INCLUDE_DIR)
    IF (NOT LIBCONFIG_INCLUDE_DIR)
        MESSAGE(FATAL_ERROR "Could not find LibConfig++ header file! Try to install 'libconfig-devel'")
    ENDIF (NOT LIBCONFIG_INCLUDE_DIR)

    IF (NOT CONFIG++_LIBRARY)
        MESSAGE(FATAL_ERROR "Could not find LibConfig++ library file! Try to install 'libconfig'")
    ENDIF (NOT CONFIG++_LIBRARY)
ENDIF (CONFIG++_LIBRARY AND LIBCONFIG_INCLUDE_DIR)

include_directories(${LIBCONFIG_INCLUDE_DIR})

message("")

#add version header
FILE(WRITE ${CMAKE_SOURCE_DIR}/inc/Version.h
        "\#pragma once\n#include <string>\nnamespace Version {\n  const std::string VERSION = \"${PROJECT_VERSION}\";\n}"
        )

add_library(api ${LIB_METHOD}
        src/api/API.cpp

        src/api/TelegramAPI.cpp

        src/api/DynuAPI.cpp

        src/api/IPAPI.cpp
        )

add_library(logger ${LIB_METHOD}
        src/FileLogger.cpp
        src/Logger.cpp
        )


set(SOURCE
        src/main.cpp
        src/IPRefresher.cpp
        src/Config.cpp)

add_executable(iprefresher ${SOURCE})

# LINK generated LIBS #
target_link_libraries(iprefresher api logger ${CURL_LIBRARIES} config++)

# INSTALL to SYSTEM #
set(CMAKE_INSTALL_PREFIX "/")
# install binaries
install(TARGETS iprefresher DESTINATION usr/bin)
# install config file if it doesn't exist
install(CODE "MESSAGE(STATUS \"Copy iprefresher.cfg to ${CMAKE_INSTALL_PREFIX}etc/iprefresher.cfg\")
    IF (NOT EXISTS ${CMAKE_INSTALL_PREFIX}etc/iprefresher.cfg)
        EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/config/iprefresher.cfg
                ${CMAKE_INSTALL_PREFIX}etc/iprefresher.cfg)
    ENDIF (NOT EXISTS ${CMAKE_INSTALL_PREFIX}etc/iprefresher.cfg)")
# install systemd service and enable it
install(FILES service/iprefresher.service DESTINATION lib/systemd/system)


IF (UNIX)
    message(STATUS "config of Package build")
    SET(CPACK_DEB_COMPONENT_INSTALL 1)
    SET(CPACK_OUTPUT_FILE_PREFIX packages)
    set(CPACK_PACKAGING_INSTALL_PREFIX "/") # no prefix for package structure

    FIND_PROGRAM(RPMBUILD_EXECUTABLE rpmbuild)
    FIND_PROGRAM(DEB_EXECUTABLE dpkg)

    SET(CPACK_GENERATOR "TGZ;TBZ2")

    #check if rpm build is possible
    if (NOT ${RPMBUILD_EXECUTABLE} STREQUAL "RPMBUILD_EXECUTABLE-NOTFOUND")
        message(STATUS "found rpm build executeable --> able to build rpm")
        set(CPACK_GENERATOR "${CPACK_GENERATOR};RPM")
        set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/lib/systemd/system" "/lib/systemd" "/lib" "/usr/local/bin" "/usr/local") # --> needed to not override existing folders
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
    SET(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
    SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${PROJECT_VERSION}")
    SET(CPACK_PACKAGE_CONTACT "Lukas Heiligenbrunner <lukas.heiligenbrunner@gmail.com>")
    SET(CPACK_PACKAGE_SECTION "games")
    set(CPACK_PACKAGE_DEPENDS "libcurl (>= 7.0.0-1), libconfig (>= 1.5.0)")

    INCLUDE(CPack)

    add_custom_target(build-linux-packages
            "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target package
            DEPENDS ${PROJECT_NAME}
            COMMENT "Installing ${PROJECT_NAME}")
    message("")
ENDIF (UNIX)

# check if Doxygen is installed
if (BUILD_DOC)
    message(STATUS "config of DOxygen build")
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        # set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

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