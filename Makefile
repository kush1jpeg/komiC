CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude
LDFLAGS :=

BIN       := komic
SRC_DIR   := src
BUILD_DIR := build

SRC := $(shell find $(SRC_DIR) -name '*.c')
OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

.PHONY: all clean test compdb

all: $(BIN)

# Link all object files into the final executable
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Compile src/foo/bar.c -> build/foo/bar.o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN)

test: all
	@echo "wire tests here later"

# Generate compile_commands.json using bear
compdb: clean
	bear -- $(MAKE) all
