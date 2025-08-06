# Compiler
CC = gcc

# Compiler flags (for debugging, warnings)
CFLAGS = -Wall -g

# Target binary
TARGET = main

# Object files
OBJS = main.o memory_manager.o slab.o

# Default rule: build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile each .c file into a .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to delete all generated files
clean:
	rm -f *.o $(TARGET)
