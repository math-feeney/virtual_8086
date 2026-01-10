#!/usr/bin/env bash
# Build script for Virtual 8086
# Author: Michael Feeney
# Date: 2025-01-02

set -eou pipefail

# 1. Preprocess
g++ -E -Iinclude src/*.cpp > 



g++ -c -g -Iinclude ./src/*.cpp

g++ -o app.out *.o