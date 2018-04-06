cmake_minimum_required(VERSION 2.8)
project(ottoTest)

## Add support for C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(PLATFORM_QNX QNX)
set(PLATFORM_UBUNTU UBUNTU)
set(CURRENT_SUPPORT_PLATFORMS ${PLATFORM_QNX} ${PLATFORM_UBUNTU})

## add generated dynamic library path
set(GENERATED_LIBRARY_PATH  ${CMAKE_SOURCE_DIR}/lib)
## add generated binary path
set(GENERATED_BINARY_PATH ${CMAKE_SOURCE_DIR}/bin)

if (CMAKE_BUILD_PLATFORM STREQUAL ${PLATFORM_QNX})
## Suppose you have already set QNX_HOST in ~/.bashrc
## Example: export QNX_BASE=$HOME/qnx700
##          export QNX_HOST=$QNX_BASE/host/linux/x86_64
## check cmake cross compiling for more details: https://cmake.org/cmake/help/v3.9/manual/cmake-toolchains.7.html
    set(tools $ENV{QNX_HOST}/usr/bin)
    ## Add compiler and linker flags
    set(CMAKE_CXX_FLAGS "-Wall -lang-c++ -Vgcc_ntox86_64")
    set(CMAKE_C_COMPILER   ${tools}/qcc)
    set(CMAKE_CXX_COMPILER ${tools}/qcc)
    ## add definitions command for diffent platforms, can be used as macro definition "#ifdef PLATFORM_QNX" in source code
    add_definitions(-DPLATFORM_QNX)
elseif(CMAKE_BUILD_PLATFORM STREQUAL ${PLATFORM_UBUNTU})
    set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
    set(CMAKE_C_COMPILER gcc)
    set(CMAKE_CXX_COMPILER g++)
    add_definitions(-DPLATFORM_UBUNTU)
else(CMAKE_BUILD_PLATFORM STREQUAL ${PLATFORM_QNX})
    message(FATAL_ERROR "The\ current\ support\ platforms\ are:\ ${CURRENT_SUPPORT_PLATFORMS}")
endif(CMAKE_BUILD_PLATFORM STREQUAL ${PLATFORM_QNX})
message(The\ c++\ compiler\ is\ set\ to\ be\ \"${CMAKE_CXX_COMPILER}\")


set(TARGET_TEST "ottoTest")
set(SRCS_TEST main.cc)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS system)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(${TARGET_TEST} ${SRCS_TEST})
    target_link_libraries(${TARGET_TEST} boost_filesystem boost_system)
    set_target_properties(${TARGET_TEST} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${GENERATED_BINARY_PATH})
    message(\"${TARGET_TEST}\"\ is\ add\ to\ ${GENERATED_BINARY_PATH})
endif()