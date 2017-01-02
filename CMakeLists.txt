cmake_minimum_required(VERSION 2.8.9)
project(DiceMaster)

#set (CMAKE_CXX_STANDARD 11) # we use C++ version 11
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

include_directories(src)
include_directories(src/command_line_interface)
set(PROG_NAME diceMaster)
set(LIB_NAME libMaster)

#Qt
find_package(Qt5Core)
find_package(Qt5Gui)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(LIB_SRC string_utility.cpp
            vector_utility.cpp
            src/constantmodifier.cpp
            src/dice.cpp
            src/diceobject.cpp
            src/diceset.cpp
            src/dicevarsmodel.cpp
            src/command_line_interface/consolewatcher.cpp
            src/command_line_interface/consoleinterface.cpp)
set(PROG_SRC main.cpp)

add_library(${LIB_NAME} STATIC ${LIB_SRC})
QT5_USE_MODULES(${LIB_NAME} Core)
QT5_USE_MODULES(${LIB_NAME} Gui)

add_executable(${PROG_NAME} ${PROG_SRC})
target_link_libraries(${PROG_NAME} ${LIB_NAME})
QT5_USE_MODULES(${PROG_NAME} Core)
