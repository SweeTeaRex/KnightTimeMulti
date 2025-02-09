# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -fsanitize=address
DEBUG_FLAGS = -g
RELEASE_FLAGS = -Wall -Wextra -O2 -s
LDFLAGS = -lraylib -lm -lpthread -ldl -lrt -lX11

# Paths (modify these based on your setup)
INCLUDE_PATH = /usr/local/include
LIBRARY_PATH = /usr/local/lib

# Directory Structure
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Project files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = game_exe

# Include Directories
INCLUDES = -I$(INC_DIR) -I$(INCLUDE_PATH)

# Compilation rules
all: debug

# Create necessary directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build target with debugging info
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(OBJ_DIR) $(TARGET)

# Build target with symbols stripped (release mode)
release: CFLAGS += $(RELEASE_FLAGS)
release: $(OBJ_DIR) $(TARGET)

# Build the target executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS) -L$(LIBRARY_PATH) $(LDFLAGS)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Run memory leak check with Valgrind
valgrind: debug
	valgrind --leak-check=full ./$(TARGET)

# Run the game
run: $(TARGET)
	LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libasan.so ./$(TARGET)

.PHONY: all debug release clean valgrind run