cmake_minimum_required(VERSION 3.7)
project(iprefresher VERSION 1.0.1 DESCRIPTION "Dynu ip refresher")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release) # manually set build type (Release / Debug)
set(libmethod STATIC) #SHARED / STATIC

find_package(CURL REQUIRED)
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

SET(CPACK_DEB_COMPONENT_INSTALL 1)

IF (UNIX)
    FIND_PROGRAM(RPMBUILD_EXECUTABLE rpmbuild)
    FIND_PROGRAM(DEB_EXECUTABLE dpkg)

    message(STATUS ${DEB_EXECUTABLE})

    SET(CPACK_GENERATOR "TGZ;TBZ2")

    #check if rpm build is possible
    if (NOT ${RPMBUILD_EXECUTABLE} STREQUAL "RPMBUILD_EXECUTABLE-NOTFOUND")
        message(STATUS "found rpm build executeable --> able to build rpm")
        set(CPACK_GENERATOR "${CPACK_GENERATOR};RPM")
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

    set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/usr/lib/systemd/system" "/usr/lib/systemd")
    INCLUDE(CPack)


ENDIF (UNIX)

add_custom_target(build-linux-packages
        "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target package
        DEPENDS ${PROJECT_NAME}
        COMMENT "Installing ${PROJECT_NAME}")

