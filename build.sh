#!/usr/bin/env bash
# Build script for Virtual 8086
# Author: Michael Feeney
# Date: 2025-01-02

set -eou pipefail

CXX=g++
CXXFLAGS="-std=c++20 -Wall -Wextra -Wpedantic -g -O0"
INCLUDES="Iinclude"

# compile
for src in src/*.cpp; do
    obj="build/$(basename "${src%.cpp}.o")"
    $CXX $CXXFLAGS $INCLUDES -c "$src" -o "$obj"
done

# Link
$CXX build/*.o -o app.out