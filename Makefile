# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Ilib
DEBUG_FLAGS = -g

# Directories
SRC_DIR = C_7
LIB_DIR = lib
OBJ_DIR = obj
LIB_OBJ_DIR = lib_obj

# Source files (change these to compile other files)
SRC_FILES = $(SRC_DIR)/free_and_sbrk.c
LIB_FILES = $(wildcard $(LIB_DIR)/*.c)

# Target executables
TARGET = demo
DEBUG_TARGET = demo_debug

# Object files
SRC_OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC_FILES)))
LIB_OBJ_FILES = $(patsubst $(LIB_DIR)/%.c, $(LIB_OBJ_DIR)/%.o, $(LIB_FILES))
DEBUG_SRC_OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/debug_%.o, $(notdir $(SRC_FILES)))
DEBUG_LIB_OBJ_FILES = $(patsubst $(LIB_DIR)/%.c, $(LIB_OBJ_DIR)/debug_%.o, $(LIB_FILES))

# Default rule to compile the program
all: $(TARGET)

$(TARGET): $(SRC_OBJ_FILES) $(LIB_OBJ_FILES)
	$(CC) $(CFLAGS) $(OPTFLAGS) -o $@ $^

# Debug build
debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(DEBUG_SRC_OBJ_FILES) $(DEBUG_LIB_OBJ_FILES)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $^

# Rule to compile .c to .o (normal build)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

$(LIB_OBJ_DIR)/%.o: $(LIB_DIR)/%.c
	@mkdir -p $(LIB_OBJ_DIR)
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

# Rule to compile .c to .o (debug build)
$(OBJ_DIR)/debug_%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

$(LIB_OBJ_DIR)/debug_%.o: $(LIB_DIR)/%.c
	@mkdir -p $(LIB_OBJ_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# Rule to clean up the build
clean:
	rm -f $(TARGET) $(DEBUG_TARGET)
	rm -f $(OBJ_DIR)/*.o $(LIB_OBJ_DIR)/*.o
	rm -f $(OBJ_DIR)/debug_*.o $(LIB_OBJ_DIR)/debug_*.o
	@rmdir $(OBJ_DIR) $(LIB_OBJ_DIR) 2>/dev/null || true

# Phony targets
.PHONY: all clean debug
