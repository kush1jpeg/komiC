CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude
LDFLAGS :=

BIN     := komic
SRC_DIR   := src
BUILD_DIR := build

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

.PHONY: all clean test compdb

all: $(BIN)

# Link the final binary from all object files
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Compile each .c into build/, creating build/ if it doesn't exist
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(BIN)

# Run everything under tests/ once you have a runner script or test binaries there
test: all
	@echo "wire this up once tests/ has something to run"

# Generates compile_commands.json so clangd stops guessing at flags/includes
# Needs `bear` installed (apt install bear / brew install bear)
compdb: clean
	bear -- $(MAKE) all
