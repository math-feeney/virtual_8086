# Compiler
CXX := g++

# Directories
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build

# Files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Flags
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -g -O0
CPPFLAGS := -I$(INC_DIR)
LDFLAGS :=

# Output
TARGET := app.out

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Ensure build dir exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Utilities
clean: 
	rm -rf $(BUILD_DIR) $(TARGET)

asm:
	objdump -S $(BUILD_DIR)/*.o | less

symbols:
	nm $(BUILD_DIR)/*.o | c++filt | less

.PHONY: all clean asm symbols
