# ---------------------------------------------------------
# COMPILER CONFIG
# ---------------------------------------------------------
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c2x -O3 \
         -Isrc -Itests/unity
LDFLAGS =

# ---------------------------------------------------------
# DIRECTORIES
# ---------------------------------------------------------
SRC_DIR      = src
TEST_DIR     = tests
UNITY_DIR    = tests/unity
BUILD_DIR    = build

# ---------------------------------------------------------
# SOURCES
# ---------------------------------------------------------

# App source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

# Remove main.o for linking tests
APP_OBJECTS_NO_MAIN = $(filter-out $(BUILD_DIR)/main.o,$(OBJECTS))

# Test source files (tests/*.c)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/test_%.o,$(TEST_SOURCES))

# Unity source files (tests/unity/*.c)
UNITY_SOURCES = $(wildcard $(UNITY_DIR)/*.c)
UNITY_OBJECTS = $(patsubst $(UNITY_DIR)/%.c,$(BUILD_DIR)/unity_%.o,$(UNITY_SOURCES))

# ---------------------------------------------------------
# EXECUTABLES
# ---------------------------------------------------------
EXECUTABLE = $(BUILD_DIR)/main.exe
TEST_RUNNER = $(BUILD_DIR)/z_test_runner.exe

# ---------------------------------------------------------
# DEFAULT
# ---------------------------------------------------------
all: $(EXECUTABLE)

# ---------------------------------------------------------
# BUILD MAIN APP
# ---------------------------------------------------------
$(EXECUTABLE): $(OBJECTS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# ---------------------------------------------------------
# OBJECT RULES
# ---------------------------------------------------------

# App objects
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Test objects
$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Unity objects
$(BUILD_DIR)/unity_%.o: $(UNITY_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------------------------------------------------
# TEST EXECUTABLE (APP WITHOUT main.o + TESTS + UNITY)
# ---------------------------------------------------------
$(TEST_RUNNER): $(APP_OBJECTS_NO_MAIN) $(TEST_OBJECTS) $(UNITY_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# ---------------------------------------------------------
# DIRECTORY CREATION
# ---------------------------------------------------------
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# ---------------------------------------------------------
# COMMAND TARGETS
# ---------------------------------------------------------
test: $(TEST_RUNNER)
	./$(TEST_RUNNER)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all test run clean
