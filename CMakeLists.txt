cmake_minimum_required(VERSION 3.7)
project(iprefresher VERSION 1.0.1 DESCRIPTION "mylib description")

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

add_library(api
        src/api/API.h
        src/api/API.cpp

        src/api/Hashmap.h

        src/api/TelegramAPI.cpp
        src/api/TelegramAPI.h

        src/api/DynuAPI.cpp
        src/api/DynuAPI.h

        src/api/IPAPI.cpp
        src/api/IPAPI.h
        )

add_library(logger
        src/Logger.cpp
        src/Logger.h
        )


set(SOURCE
        src/main.cpp
        )

add_executable(iprefresher  ${SOURCE})
target_link_libraries(iprefresher api logger ${CURL_LIBRARIES} )

install (TARGETS iprefresher DESTINATION bin)
