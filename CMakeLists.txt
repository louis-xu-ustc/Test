cmake_minimum_required(VERSION 2.8)
project(ottoTest)

## Add support for C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(PLATFORM_QNX QNX)
set(PLATFORM_UBUNTU UBUNTU)
set(CURRENT_SUPPORT_PLATFORMS ${PLATFORM_QNX} ${PLATFORM_UBUNTU})

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
    ## add generated dynamic library path
    set(GENERATED_LIBRARY_PATH  ${CMAKE_SOURCE_DIR}/lib/qnx)
    ## add generated binary path
    set(GENERATED_BINARY_PATH ${CMAKE_SOURCE_DIR}/bin/qnx)
    ## add definitions command for diffent platforms, can be used as macro definition "#ifdef PLATFORM_QNX" in source code
    add_definitions(-DPLATFORM_QNX)
elseif(CMAKE_BUILD_PLATFORM STREQUAL ${PLATFORM_UBUNTU})
    set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
    set(CMAKE_C_COMPILER gcc)
    set(CMAKE_CXX_COMPILER g++)
    set(GENERATED_LIBRARY_PATH  ${CMAKE_SOURCE_DIR}/lib/ubuntu)
    set(GENERATED_BINARY_PATH ${CMAKE_SOURCE_DIR}/bin/ubuntu)
    add_definitions(-DPLATFORM_UBUNTU)
else(CMAKE_BUILD_PLATFORM STREQUAL ${PLATFORM_QNX})
    message(FATAL_ERROR "The\ current\ support\ platforms\ are:\ ${CURRENT_SUPPORT_PLATFORMS}")
endif(CMAKE_BUILD_PLATFORM STREQUAL ${PLATFORM_QNX})
message(The\ c++\ compiler\ is\ set\ to\ be\ \"${CMAKE_CXX_COMPILER}\")

include_directories(../ottoware/src/include)

#set(TARGET_TEST1_LIB "Test1")
#set(SRCS_TEST1_LIB testClass1.cc)
#add_library(${TARGET_TEST1_LIB} SHARED ${SRCS_TEST1_LIB})
#set_target_properties(${TARGET_TEST1_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${GENERATED_LIBRARY_PATH})

#set(TARGET_TEST2_LIB "Test2")
#set(SRCS_TEST2_LIB testClass2.cc)
#add_library(${TARGET_TEST2_LIB} SHARED ${SRCS_TEST2_LIB})
#set_target_properties(${TARGET_TEST2_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${GENERATED_LIBRARY_PATH})

set(TARGET_TEST "ottoTest")
#set(SRCS_TEST main.cc)
#set(SRCS_TEST parsecmd.cc testParseCmd.cc)
#set(SRCS_TEST test.cc)
#set(SRCS_TEST testUdpConnection.cc)
#set(SRCS_TEST testMapOnQNX.cc)
set(SRCS_TEST testPubSetBuf.cc)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS system)

if(Boost_FOUND AND CMAKE_BUILD_PLATFORM STREQUAL ${PLATFORM_UBUNTU})
    include_directories(${Boost_INCLUDE_DIRS})
endif()
add_executable(${TARGET_TEST} ${SRCS_TEST})
#if(Boost_FOUND AND CMAKE_BUILD_PLATFORM STREQUAL ${PLATFORM_UBUNTU})
#target_link_libraries(${TARGET_TEST} Test boost_filesystem boost_system)
#endif()
set_target_properties(${TARGET_TEST} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${GENERATED_BINARY_PATH})
message(\"${TARGET_TEST}\"\ is\ add\ to\ ${GENERATED_BINARY_PATH})
