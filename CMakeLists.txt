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
