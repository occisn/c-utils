# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./src -I./unity
LDFLAGS = 

# Directories
SRC_DIR = src
TEST_DIR = tests
UNITY_DIR = unity
BUILD_DIR = build

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

# Unity files
UNITY_SRC = $(UNITY_DIR)/unity.c
UNITY_OBJ = $(BUILD_DIR)/unity.o

# Test files
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_EXECUTABLES = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%,$(TEST_SOURCES))

# Main executable
MAIN = main.c
EXECUTABLE = $(BUILD_DIR)/main.exe

# Default target
all: $(EXECUTABLE)

# Build main executable
$(EXECUTABLE): $(MAIN) $(OBJECTS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Build object files from source
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build Unity object file
$(UNITY_OBJ): $(UNITY_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build test executables
$(BUILD_DIR)/test_%: $(TEST_DIR)/test_%.c $(OBJECTS) $(UNITY_OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Run all tests
test: $(TEST_EXECUTABLES)
	@echo "Running all tests..."
	@for test in $(TEST_EXECUTABLES); do \
		echo "\n=== Running $$test ==="; \
		$$test || exit 1; \
	done
	@echo "\nAll tests passed!"

# Run specific test
test-%: $(BUILD_DIR)/test_%
	@echo "Running $<..."
	@$

# Run main program
run: $(EXECUTABLE)
	@$(EXECUTABLE)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all test run clean


