# Adapted from this:
# https://github.com/DallasFormulaRacing/embedded-onboarding/blob/main/section-01/README.md#example-2

CC = gcc
CFLAGS = -Wall -Iinc
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)
TARGET = build/main

.PHONY: all clean run

all: $(TARGET)

# Link obj files to into final executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

# Compile each .c file into build/
build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# Create build dir
build:
	mkdir -p build

# Clean build artifacts
clean:
	rm -rf build

# Run program
run: $(TARGET)
	./$(TARGET)