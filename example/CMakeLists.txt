cmake_minimum_required(VERSION 3.2)
project(FastCgiExample)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fpermissive")

include_directories(../)

set(SOURCE_FILES main.cpp)

set(LIBRARIES
        -L../
        fcgiwrapper
        fcgi
        pthread
        )

add_executable(fcgi_sample ${SOURCE_FILES})
target_link_libraries(fcgi_sample ${LIBRARIES})
