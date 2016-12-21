cmake_minimum_required(VERSION 2.8.9)
project(DiceMaster)

#set (CMAKE_CXX_STANDARD 11) # we use C++ version 11
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

include_directories(src)
set(PROG_NAME diceMaster)
set(LIB_NAME libMaster)

set(LIB_SRC string_utility.cpp vector_utility.cpp src/constantmodifier.cpp src/dice.cpp src/diceobject.cpp src/diceset.cpp)
set(PROG_SRC main.cpp)

add_library(${LIB_NAME} STATIC ${LIB_SRC})

add_executable(${PROG_NAME} ${PROG_SRC})
target_link_libraries(${PROG_NAME} ${LIB_NAME})
