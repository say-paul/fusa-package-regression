#!/bin/bash

# Check if a shared object path is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <path-to-shared-object>"
    exit 1
fi

# Path to the shared object
SO_PATH="$1"

# Set the LD_PRELOAD environment variable
export LD_PRELOAD=$SO_PATH

# Run the example test (e.g., a simple C program that calls malloc)
echo "Running test with LD_PRELOAD set to: $LD_PRELOAD"

# Simple test C program to demonstrate LD_PRELOAD effect
echo 'int main() { void *p = malloc(10); return 0; }' > test.c
gcc -o test test.c

# Run the test
./test

# Clean up
rm test test.c
