# Makefile

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Ilib 

# Optimization flags (default is no optimization)
OPTFLAGS = 

# Directories
SRC_DIR = C_6
LIB_DIR = lib
OBJ_DIR = obj

# Source files (change these to compile other files)
SRC_FILES = $(SRC_DIR)/setjmp_vars.c $(LIB_DIR)/error_functions.c

# Target executable
TARGET = demo

# Object files
OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC_FILES)))

# Default rule to compile the program
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OPTFLAGS) -o $@ $^

# Rule to compile .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

# Rule to clean up the build
clean:
	rm -f $(TARGET) $(OBJ_FILES)
	rmdir $(OBJ_DIR)

# Phony targets
.PHONY: all clean
