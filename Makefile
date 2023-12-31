# Compiler
CXX := g++
CC := gcc

# Compiler flags
CXXFLAGS := -g -Wall -Werror -Wextra -Wpedantic -lSDL2
CFLAGS := -g -Wall -Werror -Wextra -Wpedantic -lSDL2

# Source files directory
SRC_DIR := src

# Build directory
BUILD_DIR := build

# Output executable
TARGET := radio_operator

# Source files
SRCS_CPP := $(wildcard $(SRC_DIR)/*.cpp)
SRCS_C := $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS_CPP := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS_CPP))
OBJS_C := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS_C))

# Include directories
INC_DIRS := -Iinclude

# Libraries (if needed)
LIBS := -lSDL2

# Main target
all: $(BUILD_DIR)/$(TARGET)

# Rule to build the executable
$(BUILD_DIR)/$(TARGET): $(OBJS_CPP) $(OBJS_C)
	$(CXX) $(CXXFLAGS) $(INC_DIRS) -o $@ $^ $(LIBS)

# Rule to build C++ object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INC_DIRS) -c -o $@ $<

# Rule to build C object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC_DIRS) -c -o $@ $<

# Clean rule
clean:
	rm -rf $(BUILD_DIR)

# Run rule
run: all
	./build/$(TARGET) assets/alpha.map

# Pull changes rule
pull:
	git pull origin main

# Push rule
push:
	git add .
	git commit -m "Automated Update"
	git push origin main

# Phony target to prevent conflicts with files
.PHONY: all clean run pull push
