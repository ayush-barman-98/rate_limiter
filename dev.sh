#!/bin/bash
set -e

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Generate cmake files if needed
if [ ! -f "CMakeCache.txt" ]; then
    echo "Configuring CMake..."
    cmake ..
fi

# Build project with parallel jobs
echo "Building rate_limiter..."
make -j$(nproc)

# Run server
echo "--------------------------------------------------"
echo "Starting rate_limiter server..."
echo "--------------------------------------------------"
./rate_limiter
