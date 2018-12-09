cmake_minimum_required(VERSION 3.5)

project(Gps)

include_directories(../SerialCommunication/RaspberryPi/C++)
file(GLOB SRC_LIST *.cpp *.h
                   ../SerialCommunication/RaspberryPi/C++/SerialConnection.cpp
                   ../SerialCommunication/RaspberryPi/C++/SerialConnection.h
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14" )
add_executable(${PROJECT_NAME} ${SRC_LIST})

