cmake_minimum_required(VERSION 3.14)
project(iprefresher)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})


set(SOURCE src/main.cpp src/API.h src/API.cpp src/Hashmap.h src/Logger.cpp src/Logger.h)

add_executable(iprefresher  ${SOURCE})



target_link_libraries(iprefresher ${CURL_LIBRARIES})
