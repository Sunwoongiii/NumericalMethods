# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O2

# Target executable
TARGET = main

# Sources and objects
SOURCES = main.c machar.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = nr.h

# Default
all: $(TARGET)

# Link
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) -lm

# Compile
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Per-file deps (nr.h 포함)
main.o: main.c nr.h
machar.o: machar.c

# Utilities
clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

debug: CFLAGS += -DDEBUG
debug: $(TARGET)

.PHONY: all clean run debug