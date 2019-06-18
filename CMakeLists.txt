cmake_minimum_required(VERSION 3.7)
project(iprefresher)

set(CMAKE_CXX_STANDARD 11)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})


set(SOURCE
        src/main.cpp

        src/api/API.h
        src/api/API.cpp

        src/api/Hashmap.h

        src/Logger.cpp
        src/Logger.h

        src/api/TelegramAPI.cpp
        src/api/TelegramAPI.h

        src/api/DynuAPI.cpp
        src/api/DynuAPI.h src/api/IPAPI.cpp src/api/IPAPI.h)

add_executable(iprefresher  ${SOURCE})
target_link_libraries(iprefresher ${CURL_LIBRARIES})

install (TARGETS iprefresher DESTINATION bin)
