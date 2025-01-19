cmake_minimum_required(VERSION 3.20)
project(Strategos CXX)

# Set C++23 and UTF-8 source encoding
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-fexec-charset=UTF-8)
add_compile_options(-finput-charset=UTF-8)

# Add spdlog as a dependency
include(FetchContent)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.11.0
)
FetchContent_MakeAvailable(spdlog)

# Glob all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

# Add the executable
add_executable(Strategos ${SOURCES} ${HEADERS})

# Include directories
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR} include third_party)

# Link libraries
target_link_libraries(Strategos PRIVATE ${CURSES_LIBRARIES} spdlog::spdlog)

# Set source files to use UTF-8
if (MSVC)
    target_compile_options(Strategos PRIVATE "/utf-8")
else()
    target_compile_options(Strategos PRIVATE -finput-charset=UTF-8)
endif()