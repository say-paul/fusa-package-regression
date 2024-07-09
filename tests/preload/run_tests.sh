#!/bin/bash

# Directory where shared objects are built
BUILD_DIR="build"
# Simple test C program to demonstrate LD_PRELOAD effect
gcc -o test test.c



# Iterate over each shared object in the build directory
for so_file in $BUILD_DIR/*.so; do
    base_name=$(basename "$so_file" .so)
    export LD_PRELOAD="$BUILD_DIR/$base_name.so"
    echo "Running test with   $base_name.so"
    # Example command to run with LD_PRELOAD
    # Run the test
    ./test
done
# Clean up
rm test test.c
