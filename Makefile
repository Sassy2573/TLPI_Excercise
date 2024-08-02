# Makefile

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Ilib

# Directories
SRC_DIR = C_5
LIB_DIR = lib
OBJ_DIR = obj

# Source files (change these to compile other files)
SRC_FILES = $(SRC_DIR)/5-2.c $(LIB_DIR)/error_functions.c

# Target executable
TARGET = demo

# Object files
OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC_FILES)))

# Default rule to compile the program
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up the build
clean:
	rm -f $(TARGET) $(OBJ_FILES)
	rmdir $(OBJ_DIR)

# Phony targets
.PHONY: all clean
