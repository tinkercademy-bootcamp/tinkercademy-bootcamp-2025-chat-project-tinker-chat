all: build/server build/client

build/server: src/tcp_echo_server.cc | build
	g++ -o build/server src/tcp_echo_server.cc

build/client: src/tcp_echo_client.cc | build
	g++ -o build/client src/tcp_echo_client.cc

build:
	mkdir -p build
	
clean:
	rm -rf build