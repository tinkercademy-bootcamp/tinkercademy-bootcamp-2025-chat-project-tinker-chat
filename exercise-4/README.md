# Exercise 4

**Update this README with your answers to the questions below.**

## Learning Multi-File C++ Projects

- Move code that can be shared between `tcp_echo_server.cc` and 
  `tcp_echo_client.cc` to separate `.h` and `.cc` files
- How would you compile from the command line?
  ```sh
  g++ tcp_echo_server.cpp tcp_echo_shared.cc -o server
  ./server
  ```
  ```sh
  g++ tcp_echo_client.cpp tcp_echo_shared.cc -o client
  ./client "message"
  ```
- How would you compile using make?
  - Refer Makefile.
- How would you compile using VS Code?
  - Read `tasks.json` and `launch.json` in `.vscode`.
  

### Compiling vs Linking

- What is the difference between compiling and linking in C++?
  - Compiling converts the source files into object files while linking links all the object files to make an executable or a library.
- What is the difference between creating an executable and creating a 
  library?
  - An executable runs as a program while library is used by executables and it can be reused.
- How do you compile a library, and then use that library to compile an
  executable?
  - Compile library:  
    ```sh
    g++ -c mylib.cpp -o mylib.o  
    ar rcs libmylib.a mylib.o
    ```
  - Compile executable using library:  
    ```sh
    g++ main.cpp -L. -lmylib -o main
    ```

### Reminder 
[Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
fundamentals with practical examples and common patterns.

## Experiments in Performance

- Is it better to have many small files spread across many directories, or
  a few large files across fewer directories?
  - Small files are easy to maintain and are easy to debug.
- Is there a difference in compilation time between the two?
  - Large files may take less compile time, however, if we do changes for small files, it will recompile only those files, but for large files, even if we do a small change, it will recompile the whole file.
- How can you assess performance other than compilation speed?