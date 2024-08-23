# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Ilib
DEBUG_FLAGS = -g

# Directories
SRC_DIR = C_6
LIB_DIR = lib
OBJ_DIR = obj

# Source files (change these to compile other files)
SRC_FILES = $(SRC_DIR)/mem_segments.c #$(LIB_DIR)/error_functions.c

# Target executables
TARGET = demo
DEBUG_TARGET = demo_debug

# Object files
OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC_FILES)))
DEBUG_OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/debug_%.o, $(notdir $(SRC_FILES)))

# Default rule to compile the program
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Debug build
debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(DEBUG_OBJ_FILES)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $^

# Rule to compile .c to .o (normal build)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile .c to .o (debug build)
$(OBJ_DIR)/debug_%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

$(OBJ_DIR)/debug_%.o: $(LIB_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# Rule to clean up the build
clean:
	rm -f $(TARGET) $(DEBUG_TARGET) $(OBJ_FILES) $(DEBUG_OBJ_FILES)
	rmdir $(OBJ_DIR)

# Phony targets
.PHONY: all clean debug
