cmake_minimum_required(VERSION 3.10)
project(PRT7_Decoder CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option to build with simulation (reads from a file) instead of a serial port
option(PRT7_SIMULATION "Build with simulation input from file" ON)

if(WIN32)
  add_definitions(-DPLATFORM_WINDOWS)
else()
  add_definitions(-DPLATFORM_POSIX)
endif()

add_executable(prt7
  src/main.cpp
  src/TramaBase.h
  src/TramaLoad.h
  src/TramaLoad.cpp
  src/TramaMap.h
  src/TramaMap.cpp
  src/RotorDeMapeo.h
  src/RotorDeMapeo.cpp
  src/ListaDeCarga.h
  src/ListaDeCarga.cpp
  src/SerialPort.h
  src/SerialPort.cpp
)

if(PRT7_SIMULATION)
  target_compile_definitions(prt7 PRIVATE PRT7_SIMULATION=1)
endif()
