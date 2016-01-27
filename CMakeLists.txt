cmake_minimum_required(VERSION 3.2)
project(FastCGIWrapper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fpermissive")

set(SOURCE_FILES
        FcgiServer.h
        FcgiServer.cpp
        FcgiRequest.h
        FcgiRequest.cpp
        FcgiResponse.h
        FcgiResponse.cpp)

set(LIBRARIES
        pthread
        fcgi
        )

add_library(fcgiwrapper ${SOURCE_FILES})
target_link_libraries(fcgiwrapper ${LIBRARIES})
