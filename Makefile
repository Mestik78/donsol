CC := gcc
CFLAGS := -Wall -Wextra -O2 -Isrc
LDFLAGS := -pthread

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

CLIENT_TARGET := $(BIN_DIR)/donsol
SERVER_TARGET := $(BIN_DIR)/donsol-server

SERVER_SRCS := $(shell find $(SRC_DIR)/server -name '*.c')
SERVER_OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SERVER_SRCS))

SERVER_LIB_SRCS := $(filter-out $(SRC_DIR)/server/main.c, $(SERVER_SRCS))
SERVER_LIB_OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SERVER_LIB_SRCS))

CLIENT_ONLY_SRCS := $(shell find $(SRC_DIR)/client -name '*.c')
CLIENT_ONLY_OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(CLIENT_ONLY_SRCS))

CLIENT_OBJS := $(CLIENT_ONLY_OBJS) $(SERVER_LIB_OBJS)

.PHONY: all clean run-client run-server

all: $(CLIENT_TARGET) $(SERVER_TARGET)

$(CLIENT_TARGET): $(CLIENT_OBJS) | $(BIN_DIR)
	$(CC) $(CLIENT_OBJS) -o $@ $(LDFLAGS)

$(SERVER_TARGET): $(SERVER_OBJS) | $(BIN_DIR)
	$(CC) $(SERVER_OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $@

run-client: $(CLIENT_TARGET)
	./$(CLIENT_TARGET)

run-server: $(SERVER_TARGET)
	./$(SERVER_TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
