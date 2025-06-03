# Exercise 1

**Update this README with your answers to the questions below.**

## Learning How to Learn

- Answer the following questions in this file and commit and push your changes.
- Bonus sections are more difficult and optional.
- How can you find the information required to complete these tasks?
  - Google it 
- How can you tell if the source of your information is good?
  - Reconfirm it from multiple sources
- How would you define "good" in this situation?
  - Something which is correct (tested).

## Learn Basics of g++ CLI

- Compile the TCP client and server using `g++` from command line.
- What are the most important command line arguments to learn for `g++`?
  - -o : Allows us to choose executable file name
  - -g : Lets debugging information to be included in executable
  - -O2 -O3 -O : For Optimisation
  - -O0 : Disables optimisation
  - -Wall : To list all warnings
- What is the difference between debug vs release versions?
  - Debug versions generate debug statements and dont optimise, where as the release version has optimisation but does not generate debug statements.
- What are the tradeoffs between debug and release versions?
  - Debug versions is very slow , has a big binary , but can catch errors , assert failures easily.
  - Release versions are optimised , small. 
- What arguments would you use in a debug build?
   - g++ &nbsp; -g &nbsp; -O0 &nbsp; -o &nbsp; myexec &nbsp; file.cpp
- What about for release?
  - g++ &nbsp; -O2 &nbsp; -O3 &nbsp; -o &nbsp; myexec &nbsp; file.cpp
- What other kinds of build types are useful?
  - Release With Debug Info : Optimise Code with debug info preserved.    
  - Minimum size release: Reduces the binary file size
  - Sanitized: To catch runtime errors
  - Test : Unit tests and integration test codes included.

## Learn Basics of Make

- Create a Makefile that will speed up the process.
- [Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
  fundamentals with practical examples and common patterns.
- How else can you learn about make?
- How can you tell if the resource you are using is correct?
- Create a makefile such that when you run `make` with no arguments, it will:
  - Create `build/` directory if it does not exist
  - Create executables **client** and **server** in `build/`, if needed
  - How does make know when it needs to rebuild the executables?
    - It compares the timestamp of the file to see if it has been modified.
  - Change your Makefile such that `make clean` will remove `build/` and all
    its contents
- What are the most important command line arguments to learn for make?
  - make -f filename : Uses "filename" instead of the default makefile
  - make -c mydir , change directory to mydir before reading makefile
- What are the most important directives to learn about in Makefile?
- What are the most important commands to implement in your Makefile?
  - Appropriate Targets , like all , clean , build ,etc
  - Proper dependencies for each target
  - Variables/built in variables, using dollar()/$ dollar{} to reference them.
  - Default Target (first target, can have all as the first one to compile everything).
  - PHONY :
- Which ones are essential, which ones are nice to haves?
    - Appropriate targets is essential , variables/default variables are nice to have.
## Learn Basics of Git

- Read through the code in `src/`
- Answer any `#Questions` as a comment
- Commit and push your changes to git
- Each commit should be responding to a single task or question
- Why is it important to keep your commit to a single task or question?
  - So that there is no mixing between the work made on tasks , especially if we want to go to go to some version commited.
- Is it better to have a lot of very small commits, or one big commit when 
  everything is working? 
    - I think we should divide into subtasks before making commits of each of them , it is better to make small commits so that whatever working can be restored easily.
- What are the most important commands to know in git?
  - git status,add,merge,pull,push,pull request,fetch,rebase 

## Introduction to Sockets

- Read the code in `src/tcp-echo-client.cc` and add a way to change the 
  message sent using command line arguments
- **Example**: `./client "hello message from the command prompt"` should send
  `"hello message from the command prompt"` to the server
- Commit your changes into git
- What do all these headers do?
  - arpa/inet.h : Necessary for binary to string conversion , also used to store binary of an ip address (inet_pton) 
  - sys/socket.h : For socket API's
  - sys/types.h : Is needed to use data types required for various different calls
  - unistd.h : Needs to be used for various system calls like read.write,open,close,etc
- How do you find out which part of the below code comes from which header?
  - Comment out that header to see which parts of the code give error or cntrl click on the function/part to go to that header.
- How do you change the code so that you are sending messages to servers
  other than localhost?
  - Change the ip address of that to the server's 
- How do you change the code to send to a IPv6 address instead of IPv4?
  - Use AF_INET6 instead AF_INET6
  - Use struct sockaddr_in6 instead of struct sockaddr_in
- **Bonus**: How do you change the client code to connect by hostname instead
  of IP address?
  - Maybe run dig user, by taking command line argument of user(name) , and then just look for the appropriate ip and then select it (though will need lot of big buffer to read output)? or instead find DNS of the user and get his IP using getaddrinfo().
## Introduction to Memory Management

- What is happening in line 26 of `tcp-echo-client.cc`? 
  `if (inet_pton(AF_INET, kServerAddress.c_str(), &address.sin_addr) <= 0) {`
    - We use inet_pton to convert IP to binary and store in address , we also check if it returns a non positive value which indicates that the given IP address was not found/supported.
- What is happening in line 31 of `tcp-echo-client.cc`?
  `if (connect(my_sock, (sockaddr *)&address, sizeof(address)) < 0) {`
  - It sends a connection request to server , <0 if it fails , 0 is returned if success. Address (second parameter) searches for server's IP to connect. It opens a connection on the file descriptor (my_sock) which is closed at the end of the code.
- What is the difference between a pointer and a reference?
  - Pointer refers to something which stores memory of something. It can be changed to store memory of something else or even (null). Whereas, reference is just an alias of a quantity , it can't be modified to be an alias of something else and on changing value of it (the original value also changes). 
- When is it better to use a pointer?
  - Dynamic memory allocation , traversing something,etc
- When is it better to use a reference?
  - When a function needs to modify the original variable passed as an argument. This avoids copying large objects and allows direct modification.
- What is the difference between `std::string` and a C-style string?
  - Memory of `std::string` is managed automatically , whereas we have to manually manage for cstrings. Cstring ends with '\0', othing like that for strings .
- What type is a C-style string?
  - char *
- What happens when you iterate a pointer?
  - It points to the memory of the quantity stored in the new memory (depends on which data type is iterated).Dereferencing it gives value of that new quantity.
- What are the most important safety tips to know when using pointers?
  - Free/delete malloced/new'ed pointers or else it just leaks memory.Don't use a pointer after freed. Don't dereference nullpointers. 
## Learn Basics of Creating a C++ Project in Your IDE

- How do you compile and run your project in your IDE?
  - Use make to compile and just run the executables to run in our IDE.
## Improving Interactions with LLMs

- What is the most authoritative source of information about `socket()`
  from `<sys/socket.h>`?
  - POSIX specifications ,man 2 socket
- What is the most authoritative source of information about the TCP and IP
  protocols?
   -  Internet Engineering Task Force (IETF) 
- What is the most authoritative source of information about the C++
  programming language?
   - Cppreference.com and The ISO C++ Standard.
- What information can you find about using Markdown when structuring prompts 
  to LLMs?
    - It improves prompt readability for both the user and model, the model can read bold, italicised texts , headers and code blocks easily.
- What is the difference between LLM and AI?
  - LLM's are a type of AI model which is trained on certain data, whereas AI is any machine which performs tasks which requires human abilities , like undestanding , reasoning ,etc.
- Is it grammatically correct in English to say "a LLM" or "an LLM"? Why?
  - It is an LLM (because el-el-em).