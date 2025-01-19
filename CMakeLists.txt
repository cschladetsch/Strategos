
cmake_minimum_required(VERSION 3.20)
project(Strategos CXX)

set(CMAKE_CXX_STANDARD 23)

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
