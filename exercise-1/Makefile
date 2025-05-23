all: build/server build/client
build/server: src/tcp_echo_server.cc
	mkdir -p build
	g++ -o build/server src/tcp_echo_server.cc

build/client: src/tcp_echo_client.cc
	mkdir -p build
	g++ -o build/client src/tcp_echo_client.cc

clean:
	rm -rf build