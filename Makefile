# Define the compiler and flags
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11

# Define the directories for object files, includes, source, bin, and tests
OBJ_DIR=obj
INCLUDE_DIR=include
SRC_DIR=src
BIN_DIR=bin
EXEC=clackjack
TEST_DIR=test
TEST_FILE=test_runner

# Define the source files and object files
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Define the test source files and test object files
TEST_SRC_FILES=$(wildcard $(TEST_DIR)/*.c)
TEST_OBJ_FILES=$(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_SRC_FILES))


# Define the target executable
TARGET=$(BIN_DIR)/$(EXEC)
TEST_TARGET=$(BIN_DIR)/$(TEST_FILE)


# Define the command for compiling the target executable
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $@
	make test


# Define the command for compiling the object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $^ -o $@


# Define the command for compiling the test executable
$(TEST_TARGET): $(TEST_OBJ_FILES) $(filter-out $(OBJ_DIR)/main.o, $(OBJ_FILES))
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $@


# Define the command for compiling the test object files
$(TEST_OBJ_FILES): $(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@


.PHONY: test

# Define the command for running the test executable
test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*
