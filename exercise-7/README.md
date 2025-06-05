# Exercise 7

**Update this README with your answers to the questions below.**

## Resources for Learning About EPOLL

- https://suchprogramming.com/epoll-in-3-easy-steps/ 
- https://github.com/onestraw/epoll-example/
- https://github.com/joakimthun/io-uring-echo-server
- https://man7.org/linux/man-pages/man7/epoll.7.html
- What other resources can you find about epoll?
  - "Linux System Programming" by Robert Love
- Are the above code repos examples of good code or bad code?
  - No separation of files, no error handling, no directory structure but easy to read.
- How do you decide what is good code or bad code?
  - A good code is well structured, has a clear separation of concerns, 
    has error handling, and is easy to read and maintain. Bad code is messy, 
    hard to read, and lacks structure.

## Creating a Chat Client/Server Using EPOLL

- Use the above resources and what you have learned to start a brand new C++ 
  project
- The server should be able to accept multiple connections at a time, as many
  as you can, to chat with each other
- Each client should be able to communicate with the server in some way so 
  that each client can be assigned a **username**
- Each client can send at least the following commands:
  - List channels
  - Go to channel
  - Create channel
- Whenever a user types in a message, it should be displayed to everyone else 
  in the channel
- You are free to come up with any other commands that you like
- You can use any directory structure or any makefile that you like
- You can use any 3rd party open source library that you like
- However for the purposes of this bootcamp, please stay with make and bash 
  scripts
- `cmake`, `ninja`, `conan` and `vcpkg` are all useful tools but are out of 
  scope for this bootcamp
- Some libraries that are likely to be useful:
- `sudo apt get ncurses-dev`
- For the more ambitious: `sudo apt get libsdl2-dev`

## Adding a Third Party Library from Source

- Not all useful open source libraries will be available as a debian package
- For the purposes of this workshop, your only options are to install a 
  shared library into `usr/include` and `usr/lib`, or to git clone
  the source code and build it
- What are the tradeoffs between using a library from `usr/lib` vs git cloning
  the source and using that instead?
  - Using a library from `usr/lib` is easier and faster to set up, but it may not
    be the latest version or may not have the features you need. Cloning the source
    allows you to modify the library, but requires more setup and maintenance.
- What is the difference between `-l` and `-L` when linking using `g++`?
  - `-l` specifies the name of the library to link against, while `-L` specifies the
    directory where the library is located.