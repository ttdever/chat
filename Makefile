CC = gcc
CFLAGS = -Wall
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = out
BIN_DIR = bin
LDFLAGS = -lws2_32 -lshlwapi

# Collect all .c files in the source directory
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Generate a list of corresponding .o files in the object directory
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Set the include directories
INC = -I$(INCLUDE_DIR)

# Set the output executable
TARGET = $(BIN_DIR)/chat

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ $(LDFLAGS)

# Rule to build object files from source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# Clean rule
clean:
	del /Q $(OBJ_DIR)\*.o
	del /Q $(BIN_DIR)\*

run:
	$(BIN_DIR)/chat.exe

.PHONY: all clean
