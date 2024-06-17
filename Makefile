# Compiler and flags
CC := gcc
CFLAGS := -fPIC -Wall -Werror -Wextra
LDFLAGS := -shared

# Directories and files
OBJ_DIR := obj
SRC := $(wildcard *.c)
OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)
TARGET := ft_malloc.so

# Static library
STATIC_LIB_DIR := ./libft
STATIC_LIB := $(STATIC_LIB_DIR)/libft.a

# Default target
all: $(TARGET)

# Rule to build the shared object, including the static library
$(TARGET): $(OBJ) $(STATIC_LIB)
	$(CC) $(LDFLAGS) -o $@ $^ $(STATIC_LIB)

# Rule to compile source files to object files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Rule to build the static library using its own Makefile
$(STATIC_LIB):
	$(MAKE) -C $(STATIC_LIB_DIR)

# Clean up generated files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Clean up all generated files, including the static library
fclean: clean
	$(MAKE) -C $(STATIC_LIB_DIR) fclean

# Rebuild everything from scratch
re: fclean all

.PHONY: all clean fclean re