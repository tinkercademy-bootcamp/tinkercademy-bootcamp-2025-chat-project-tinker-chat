CXX = g++
CXX_FLAGS = -O2 -std=c++17 -fno-exceptions -fno-rtti
CXX_FLAGS += -fomit-frame-pointer -march=native

SRC = tcp_echo_client.cc
ASM = $(SRC:.cc=.s)

all: $(ASM)

%.s: %.cc
	$(CXX) $(CXX_FLAGS) -S $< -o $@

clean:
	rm -f *.s
