# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -g -Wall -Werror -Wextra -Wpedantic

# Source files directory
SRC_DIR := src

# Build directory
BUILD_DIR := build

# Output executable
TARGET := radio_operator

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Include directories
INC_DIRS := -Iinclude

# Libraries (if needed)
LIBS :=

# Main target
all: $(BUILD_DIR)/$(TARGET)

# Rule to build the executable
$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INC_DIRS) -o $@ $^ $(LIBS)

# Rule to build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INC_DIRS) -c -o $@ $<

# Clean rule
clean:
	rm -rf $(BUILD_DIR)

# Run rule
run: all
	./build/$(TARGET) assets/alpha.map

# Phony target to prevent conflicts with files named "clean," "all," or "run"
.PHONY: all clean run