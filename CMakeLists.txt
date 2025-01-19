cmake_minimum_required(VERSION 3.20)
project(Strategos CXX)

set(CMAKE_CXX_STANDARD 23)

# Check if rang.hpp exists and download it if necessary
set(RANG_HEADER_PATH "${CMAKE_SOURCE_DIR}/third_party/rang.hpp")
if(NOT EXISTS ${RANG_HEADER_PATH})
    message(STATUS "rang.hpp not found, downloading...")
    file(DOWNLOAD
        https://raw.githubusercontent.com/agauniyal/rang/master/include/rang.hpp
        ${RANG_HEADER_PATH}
        STATUS status
    )
    list(GET status 0 status_code)
    if(NOT status_code EQUAL 0)
        message(FATAL_ERROR "Failed to download rang.hpp. Please check your network connection.")
    endif()
endif()

# Glob all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

# Add executable target
add_executable(Strategos ${SOURCES} ${HEADERS})

# Include directories for headers
target_include_directories(Strategos PRIVATE include third_party)

