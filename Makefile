#! /bin/bash

# Compiler and compiler flags
CC = gcc
CFLAGS = -std=c11 -Wall

# Directories
SRC_DIR = app
BUILD_DIR = build
BIN_DIR = bin

# Source files
CLIENT_SRC = $(SRC_DIR)/client/src/rc1.c $(SRC_DIR)/client/include/header.h $(SRC_DIR)/client/include/semun.h $(SRC_DIR)/common/dataStruct.h

# Output binaries
CLIENT_BIN = $(BIN_DIR)/client
SERVER_BIN = $(BIN_DIR)/server

# Targets
all: $(CLIENT_BIN) $(SERVER_BIN)

$(CLIENT_BIN): $(CLIENT_SRC)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(CLIENT_SRC) -o $(CLIENT_BIN)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)