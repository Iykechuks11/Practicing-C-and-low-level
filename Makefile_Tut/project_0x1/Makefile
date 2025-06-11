# Define a variable for the C compiler
CC = gcc

# Define compiler flags (enable all warnings, include debug information)
CFLAGS = -Wall -g

# Define the build directory
BUILD_DIR = build

# Define source files
SRCS = main.c utils.c

# Define object files (they will be in the build directory)
# $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS)) takes SRCS, changes .c to .o, and prepends BUILD_DIR/
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

# Define the executable name (it will also be in the build directory)
TARGET = $(BUILD_DIR)/my_program

# The default target: our executable program
# It depends on the object files
# The @mkdir -p $(BUILD_DIR) creates the build directory if it doesn't exist
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "Program built successfully."

# Rule to build object files in the build directory
# This is a pattern rule: it applies to any .o file in BUILD_DIR that has a corresponding .c file
$(BUILD_DIR)/%.o: %.c utils.h | $(BUILD_DIR) # The | $(BUILD_DIR) makes $(BUILD_DIR) an order-only prerequisite
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create the build directory (order-only prerequisite)
# This ensures the directory exists before trying to put files in it.
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Phony target to clean up build files
clean:
	@echo "Cleaning up..."
	rm -rf $(BUILD_DIR) # Remove the entire build directory
	@echo "Cleaned."

# Phony target to list files to prevent 'make' from thinking 'clean' is a file
.PHONY: all clean