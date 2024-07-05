#!/bin/bash

# Create a directory for the build output
mkdir -p build

# Compile each C file in the src directory into a shared object
for src_file in src/*.c; do
    base_name=$(basename "$src_file" .c)
    # Compile the C file into a shared object
    if gcc -fPIC -shared -o "build/lib${base_name}.so" "$src_file"; then
        echo "Shared object 'lib${base_name}.so' built successfully."
    else
        echo "Failed to build shared object 'lib${base_name}.so'."
    fi
done
