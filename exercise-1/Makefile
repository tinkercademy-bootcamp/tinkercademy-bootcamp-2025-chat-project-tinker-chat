all: server client

BUILD_DIR = ./build
SRC_DIR = ./src

server: $(SRC_DIR)/tcp_echo_server.cc
	mkdir -p $(BUILD_DIR)
	g++ $(SRC_DIR)/tcp_echo_server.cc -o $(BUILD_DIR)/server

server_obj
client: $(SRC_DIR)/tcp_echo_client.cc
	mkdir -p $(BUILD_DIR)
	g++ $(SRC_DIR)/tcp_echo_client.cc -o $(BUILD_DIR)/client

clean:
	rm -rf $(BUILD_DIR)	