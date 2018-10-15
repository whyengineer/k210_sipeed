### This file is used for build example projects.

# set this will supress some warnings
set(BUILDING_SDK "yes" CACHE INTERNAL "")

cmake_minimum_required(VERSION 3.0)
include(${SDK}/cmake/common.cmake)
project(hello_world)


INCLUDE_DIRECTORIES(${SDK}/lib/arch/include ${SDK}/lib/utils/include)
# config self use headers
header_directories(${SDK}/lib)
# build library first
add_subdirectory(${SDK}/lib SDK)

# TODO
#add_subdirectory(third_party)

# compile project
add_source_files(src/*.c)
include(${SDK}/cmake/executable.cmake)


add_custom_target(flash ${PORT}
    COMMAND ${CMAKE_COMMAND} ARGS -DDEVICE=${DEVICE} -DTOOL=${TOOL} -DNAME=${CMAKE_PROJECT_NAME} -P ${TOOL}/flash/flash.cmake
)


