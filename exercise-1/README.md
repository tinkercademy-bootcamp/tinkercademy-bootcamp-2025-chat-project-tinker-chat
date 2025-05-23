# Exercise 1

**Update this README with your answers to the questions below.**

## Learning How to Learn

- Answer the following questions in this file and commit and push your changes.
- Bonus sections are more difficult and optional.
- How can you find the information required to complete these tasks?
- How can you tell if the source of your information is good?
- How would you define "good" in this situation?

## Learn Basics of g++ CLI

- Compile the TCP client and server using `g++` from command line.
  - g++ -std=c++20 tcp_echo_client.cc -o tcp_echo_client
  - g++ -std=c++20 tcp_echo_server.cc -o tcp_echo_server
- What are the most important command line arguments to learn for `g++`?
  - -o, -g, -std=, -O2, -O3
- What is the difference between debug vs release versions?
  - Debug version preserves variable names and line numbers so that it's easier to trace the program execution with tools like gdb and valgrind, while release version heavily optimizes the code for performance
- What are the tradeoffs between debug and release versions?
  - Debug version: Improved debugging for the cost of larger binaries and slower performance
  - Release version: Fast performance and smaller binaries for the cost of harder debugging
- What arguments would you use in a debug build?
  - -g
- What about for release?
  - -O2 or -O3
- What other kinds of build types are useful?
  - Sanitized: to catch runtime errors
  - Minimum size release: optimizes for the file size of the binary  

## Learn Basics of Make

- Create a Makefile that will speed up the process.
- [Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
  fundamentals with practical examples and common patterns.
- How else can you learn about make?
  - Ask an LLM to give the Makefile code along with line-by-line explanation
- How can you tell if the resource you are using is correct?
  - Verify correctness by running it on my system
- Create a makefile such that when you run `make` with no arguments, it will:
  - Create `build/` directory if it does not exist
  - Create executables **client** and **server** in `build/`, if needed
  - How does make know when it needs to rebuild the executables?
    - Looks at the last modified timestamps of all dependencies of an executable
    - If any timestamp is newer than the time since the last make, then it rebuilds the executable
  - Change your Makefile such that `make clean` will remove `build/` and all
    its contents
- What are the most important command line arguments to learn for make?
  - all: default target
  - clean: deletes files created as a result of make (like executables)
  - -f filename: can be used to specify the Makefile's filename (default is Makefile)
- What are the most important directives to learn about in Makefile?
  - all: default target
  - clean: deletes files created as a result of make (like executables)
  - pattern rules (%.o: %.cpp): avoids repetition of code to build different files with the same command 
  - .PHONY: declares targets that are not files; for eg, if we have a file `clean.cc` which compiles to `clean.o` on build, and we run `make clean` without declaring clean as `.PHONY`, make looks at the file `clean.o`, sees that it's up to date and does nothing 
- What are the most important commands to implement in your Makefile?
  - `all`
  - `clean`
  - build commands for specific files

- Which ones are essential, which ones are nice to haves?
  - `all` is essential
  - `clean` is nice to have
  - build commands may be essential if some file needs to be compiled
  
## Learn Basics of Git

- Read through the code in `src/`
- Answer any `#Questions` as a comment
- Commit and push your changes to git
- Each commit should be responding to a single task or question
- Why is it important to keep your commit to a single task or question?
- Is it better to have a lot of very small commits, or one big commit when 
  everything is working?
- What are the most important commands to know in git?

## Introduction to Sockets

- Read the code in `src/tcp-echo-client.cc` and add a way to change the 
  message sent using command line arguments
- **Example**: `./client "hello message from the command prompt"` should send
  `"hello message from the command prompt"` to the server
- Commit your changes into git
- What do all these headers do?
- How do you find out which part of the below code comes from which header?
- How do you change the code so that you are sending messages to servers
  other than localhost?
- How do you change the code to send to a IPv6 address instead of IPv4?
- **Bonus**: How do you change the client code to connect by hostname instead
  of IP address?
  
## Introduction to Memory Management

- What is happening in line 26 of `tcp-echo-client.cc`? 
  `if (inet_pton(AF_INET, kServerAddress.c_str(), &address.sin_addr) <= 0) {`
- What is happening in line 31 of `tcp-echo-client.cc`?
  `if (connect(my_sock, (sockaddr *)&address, sizeof(address)) < 0) {`
- What is the difference between a pointer and a reference?
- When is it better to use a pointer?
- When is it better to use a reference?
- What is the difference between `std::string` and a C-style string?
- What type is a C-style string?
- What happens when you iterate a pointer?
- What are the most important safety tips to know when using pointers?

## Learn Basics of Creating a C++ Project in Your IDE

- How do you compile and run your project in your IDE?

## Improving Interactions with LLMs

- What is the most authoritative source of information about `socket()`
  from `<sys/socket.h>`?
- What is the most authoritative source of information about the TCP and IP
  protocols?
- What is the most authoritative source of information about the C++
  programming language?
- What information can you find about using Markdown when structuring prompts 
  to LLMs?
- What is the difference between LLM and AI?
- Is it grammatically correct in English to say "a LLM" or "an LLM"? Why?