# Define the compiler
CC = gcc

# Compiler flags
CFLAGS = -std=c99 -ggdb -Wall -Wextra -pedantic
CLIBFLAGS = -lm

# Define the executable name
TARGET = wildfire

# Source files
SRC = wildfire.c process_cmdln_args.c display.c grid_forest.c

# Object files (derived from source files)
OBJ = $(SRC:.c=.o)

# Default rule to build the target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(CLIBFLAGS)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: all clean	