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
- What are the most important command line arguments to learn for `g++`?
  - use `g++ file.cpp -o file` to make binary file named `file`.
  - use `g++ -c file.cpp` to just compile and make an object file named `file.o`. 
  - use `g++ file1.o file2.o -o output` to link both the files and create an executable named `output`.
  - use `g++ -g file.cpp -o output` to use gdb (a debugging tool).
  - use `g++ -O2 file.cpp` to optimize the code.
- What is the difference between debug vs release versions?
  - The debug mode is for development period while you are coding which helps in debugging it better. It does not automatically make the code faster by doing some optimisations so this will help in debugging as the code is not changed. Release mode is used after whole code is done as it does optimisations which will make the code faster.
- What are the tradeoffs between debug and release versions?
  - In the debug mode, the code runs slower as there ae no optimisations, while in the release mode, we cannot debug.
- What arguments would you use in a debug build?
  - `g++ -g -O0 -Wall -Wextra -o output file.cpp` can be used. Here, -g is to use gdb debugger, -O0 means no optimisation, -Wall and -Wextra will give all the warnings in compiling the code.
- What about for release?
  - `g++ -O2 -DNDEBUG -Wall -Wextra -o output file.cpp` can be used. Here, -O2 is for optimising code and -DNDEBUG disbales all assert statements to make the code ready for release.
- What other kinds of build types are useful?
  - We can have debug + release mode in which there will be optimisation but we'll use the `-g` flag so that some debugging can happen and is useful for stack traces and profiling tools (e.g. gdb, valgrind).
  - Mininimum Size Release in which we use the `-Os` flag to minimise the size. It may be used when there is a constraint on the size of the binary.
  - There is Custom Testing Build with flag `-DTESTING` which helps us to run test-only code.

## Learn Basics of Make

- Create a Makefile that will speed up the process.
- [Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
  fundamentals with practical examples and common patterns.
- How else can you learn about make?
  - Using `man make` or StackOverflow.
- How can you tell if the resource you are using is correct?
  - The manual is in itself a right resource, as it is an official document. For StackOverflow, or any other blog, we can confirm from many resoiurces or compare it with the manual, or test it out by making our own Makefile. 
- Create a makefile such that when you run `make` with no arguments, it will:
  - Create `build/` directory if it does not exist
  - Create executables **client** and **server** in `build/`, if needed
  - How does make know when it needs to rebuild the executables?
    - We can add dependency files, and whenever those files change, it need to rebuild the executables.
  - Change your Makefile such that `make clean` will remove `build/` and all
    its contents
- What are the most important command line arguments to learn for make?
  - make runs the first target (or all if it is there)
  - make target runs that target
  - `make -f <filename>` runs a different Makefile.
  - `make -B` force rebuilds all the targets.
  - `make -C <dir>` runs make from another directory.
  - `make -n` prints the commands that would be executed.
  - `make -t` touche files instead of running their commands.
- What are the most important directives to learn about in Makefile?
  - target: dependencies (Defines a build rule so that target is rebuilt when one of the dependencies change)
  - all: (default target)
  - clean: (deletes generated files)
  - PHONY (declares targets that are not files)
- What are the most important commands to implement in your Makefile?
  - `g++`, `mkdir -p`, `echo` are the most used and important commands fo make.
- Which ones are essential, which ones are nice to haves?
  - Essential commands: `g++` (for compiling source files), `mkdir -p` (to ensure the build directory exists), and `rm -rf` (for cleaning up build artifacts) are necessary for basic build and clean operations.
  - Nice to have: `echo` (for informative messages), and additional shell commands for more advanced automation or user feedback, but they are not strictly required for a functional Makefile.

## Learn Basics of Git

- Read through the code in `src/`
- Answer any `#Questions` as a comment
- Commit and push your changes to git
- Each commit should be responding to a single task or question
- Why is it important to keep your commit to a single task or question?
  It is generally better to have a lot of very small commits rather than one big commit. Small commits make it easier to understand the history of changes, review code, and identify where bugs were introduced. Each commit should represent a single logical change, which improves collaboration and makes it easier to revert or modify specific changes if needed.
  everything is working?
  - Keeping the commit to single task will help in reviewing the code easily, and in understanding the history of changes. It will be easier to debug the code, if any error occurs.
- Is it better to have a lot of very small commits, or one big commit when 
  everything is working?
  - It's better to have a lot of very small commits as each commit will represent a single logical change which will help in identifying where the bug was introduced and if working on a team project, it will help the other person to understand what you've done. 
- What are the most important commands to know in git?
  - `git init` – Initialize a new git repository.
  - `git clone <repo-url>` – Clone an existing repository.
  - `git status` – Show the status of changes as untracked, modified, or staged.
  - `git add <file>` – Stage changes for commit.
  - `git commit -m "message"` – Commit staged changes with a message.
  - `git log` – View commit history.
  - `git diff` – Show changes between commits, commit and working tree, etc.
  - `git branch` – List, create, or delete branches.
  - `git checkout <branch>` – Switch branches or restore files.
  - `git merge <branch>` – Merge another branch into the current branch.
  - `git pull` – Fetch and merge changes from a remote repository.
  - `git push` – Push local commits to a remote repository.
  - `git remote` – Manage set of tracked repositories.
  - `git reset` – Undo changes by resetting current HEAD to a specified state.

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