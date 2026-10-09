CC := gcc
CFLAGS := -Wall -Wextra -O3 -flto -march=native -Isrc -ffunction-sections -fdata-sections
LDFLAGS := -pthread -flto -Wl,--gc-sections -Wl,-s

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

CLIENT_TARGET := $(BIN_DIR)/donsol
SERVER_TARGET := $(BIN_DIR)/donsol-server

SERVER_SRCS := $(shell find $(SRC_DIR)/server -name '*.c')
SERVER_LIB_SRCS := $(filter-out $(SRC_DIR)/server/main.c, $(SERVER_SRCS))

COMMON_SRCS := $(shell find $(SRC_DIR)/common -name '*.c')
COMMON_OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(COMMON_SRCS))

SERVER_OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SERVER_SRCS)) $(COMMON_OBJS)
SERVER_LIB_OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SERVER_LIB_SRCS)) $(COMMON_OBJS)

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
