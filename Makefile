ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
# Compiler and flags
CC := gcc
CFLAGS := -fPIC -Wall -Werror -Wextra -g3
LDFLAGS := -shared

# Directories and files
OBJ_DIR := obj
SRC := $(wildcard *.c)
OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)
TARGET := libft_malloc_$(HOSTTYPE).so
SYMLINK := libft_malloc.so

# Static library
STATIC_LIB_DIR := ./libft
STATIC_LIB := $(STATIC_LIB_DIR)/libft.a
STATIC_LIB_DIR_PRINTF := ./printf
STATIC_LIB_PRINTF := $(STATIC_LIB_DIR_PRINTF)/libftprintf.a



# Default target
all: $(TARGET)

# Rule to build the shared object, including the static library
$(TARGET): $(OBJ) $(STATIC_LIB)
	$(CC) $(LDFLAGS) -o $@ $^ $(STATIC_LIB) $(STATIC_LIB_PRINTF)
	@if [ -L libft_malloc.so ]; then rm libft_malloc.so; fi
	ln -s $(TARGET) $(SYMLINK)


# Rule to compile source files to object files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Rule to build the static library using its own Makefile
$(STATIC_LIB):
	@$(MAKE) -C $(STATIC_LIB_DIR)
	@$(MAKE) -C $(STATIC_LIB_DIR_PRINTF)

# Clean up generated files
clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(SYMLINK)
	rm -f test

#exec ./test to test ft_malloc
test: all
	@$(CC) -Wall -Werror -Wextra -g3 -c main.c
	@$(CC) -Wall -Werror -Wextra -g3 main.o -o $@ -L. -lft_malloc_$(HOSTTYPE) -Wl,-rpath,.
	ulimit -v 1048576; ./test $(TARGET)
	@rm -f main.o test

vtest: all
	@$(CC) -Wall -Werror -Wextra -g3 -c main.c
	@$(CC) -Wall -Werror -Wextra -g3 main.o -o $@ -L. -lft_malloc_$(HOSTTYPE) -Wl,-rpath,.
	valgrind -s ./test $(TARGET)
	@rm -f main.o vtest

# Clean up all generated files, including the static library
fclean: clean
	$(MAKE) -C $(STATIC_LIB_DIR) fclean
	$(MAKE) -C $(STATIC_LIB_DIR_PRINTF) fclean

# Rebuild everything from scratch
re: fclean all

.PHONY: all clean fclean re