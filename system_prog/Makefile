# Makefile

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -g

# Source files
SRC = open_acm_test.c

# Executable file
TARGET = acm.out

# Default target
all: $(TARGET)

# Compile the source files into the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Clean up
clean:
	rm -f $(TARGET)
