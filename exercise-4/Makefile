CXX := g++
CXXFLAGS := -O3 -std=c++23 -fsanitize=address
LDFLAGS := -fsanitize=address

SRC_DIR := src
BUILD_DIR := build

SERVER_SRC := $(SRC_DIR)/tcp_echo_server.cpp
CLIENT_SRC := $(SRC_DIR)/tcp_echo_client.cpp
SHARED_SRC := $(SRC_DIR)/tcp_echo_shared.cc

SERVER := $(BUILD_DIR)/server
CLIENT := $(BUILD_DIR)/client

all: $(SERVER) $(CLIENT)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(SERVER): $(SERVER_SRC) $(SHARED_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(CLIENT): $(CLIENT_SRC) $(SHARED_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
