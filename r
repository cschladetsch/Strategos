#!/bin/bash

find . -type f -name '*Identifier*' -exec rm -v {} \;

# Create and navigate to the build directory
mkdir -p build && cd build

# Run CMake to generate the build system
cmake ..

# Build the project
make

# Execute the program if the build succeeded
if [ $? -eq 0 ]; then
    ./Strategos
else
    echo "Build failed."
fi
