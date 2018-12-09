cmake_minimum_required(VERSION 3.5)

project(SerialCommunication)
file(GLOB SRC_LIST *.cpp *.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14" )
add_executable(${PROJECT_NAME} ${SRC_LIST})

