cmake_minimum_required(VERSION 3.7)
project(iprefresher VERSION 1.0.1 DESCRIPTION "Dynu ip refresher")

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_BUILD_TYPE Release) # manually set build type

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR} inc)

add_library(api
        src/api/API.cpp


        src/api/TelegramAPI.cpp

        src/api/DynuAPI.cpp

        src/api/IPAPI.cpp
        )

add_library(logger
        src/Logger.cpp
        )


set(SOURCE
        src/main.cpp
        src/IPRefresher.cpp inc/IPRefresher.h)

add_executable(iprefresher  ${SOURCE})

# LINK generated LIBS #
target_link_libraries(iprefresher api logger ${CURL_LIBRARIES} )

# INSTALL to SYSTEM #
install (TARGETS iprefresher DESTINATION bin)

SET(CPACK_DEB_COMPONENT_INSTALL 1)

IF (UNIX)

    SET(CPACK_CMAKE_GENERATOR "Unix Makefiles")
    SET(CPACK_SOURCE_GENERATOR "TGZ;TBZ2")
    SET(CPACK_GENERATOR "TGZ;TBZ2;DEB;RPM")
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

ENDIF (UNIX)

add_custom_target(build-linux-packages
        "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target package
        DEPENDS ${PROJECT_NAME}
        COMMENT "Installing ${PROJECT_NAME}")

