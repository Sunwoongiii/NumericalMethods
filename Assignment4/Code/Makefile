# Makefile for Homework #4: Random Number Generation

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wno-unused-variable -O2
LDFLAGS = -lm

# Target executable
TARGET = main

# Source files - RAN1.C와 GASDEV.C 포함 필수!
SOURCES = main.c ran1.c gasdev.c
HEADERS = nr.h nrutil.h
OBJECTS = $(SOURCES:.c=.o)

# Python script
PYTHON_SCRIPT = histogram.py
PYTHON = python3

# Output files
DATA_FILES = uniform_*.txt gaussian_*.txt
IMAGE_FILES = uniform_histograms.png gaussian_histograms.png comparison_histograms.png

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Generate samples
samples: $(TARGET)
	./$(TARGET)

# Generate histograms (requires samples)
histograms: samples
	$(PYTHON) $(PYTHON_SCRIPT)

# Run everything (samples + histograms)
run: histograms
	@echo "All done! Check the PNG files for visualizations."

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

# Clean all generated files
clean-all: clean
	rm -f $(DATA_FILES) $(IMAGE_FILES)

# Rebuild everything
rebuild: clean-all all

# Help
help:
	@echo "Available targets:"
	@echo "  make              - Compile the program"
	@echo "  make samples      - Generate random samples"
	@echo "  make histograms   - Generate histograms (requires samples)"
	@echo "  make run          - Generate samples and histograms"
	@echo "  make clean        - Remove compiled files"
	@echo "  make clean-all    - Remove all generated files"
	@echo "  make rebuild      - Clean and compile everything"
	@echo "  make help         - Show this help message"

.PHONY: all samples histograms run clean clean-all rebuild help
