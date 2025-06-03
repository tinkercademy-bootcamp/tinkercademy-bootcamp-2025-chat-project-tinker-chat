# Exercise 2

**Update this README with your answers to the questions below.**

## Sources of Information for Questions from Before

### Socket 
- https://man7.org/linux/man-pages/man2/socket.2.html - System call reference
  for creating communication endpoints
- Or type `man socket` in terminal
- https://man7.org/linux/man-pages/man7/socket.7.html - Socket interface 
  overview and protocol families
- Or type `man 7 socket` in terminal
- When would you want to use a `SOCK_RAW` stream?
  - A raw socket allows an application to directly access lower level protocols, which means a raw socket receives un-extracted packets . There is no need to provide the port and IP address to a raw socket, unlike in the case of stream and datagram sockets.

### TCP and IP Protocols
- [IPv4](https://www.rfc-editor.org/info/rfc791) - Internet Protocol 
  specification defining packet structure and routing
- [IPv6](https://www.rfc-editor.org/info/rfc8200) - Next-generation Internet 
  Protocol with expanded address space
- [TCP](https://datatracker.ietf.org/doc/html/rfc9293) - Transmission Control 
  Protocol providing reliable, ordered data delivery
    
### C++
- [C++23 ISO standard draft](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4950.pdf) - 
  Working draft of the C++ language specification
- Is the above the official C++23 spec? 
  - No, this is not the official C++ 23 . The official spec needs to be purchased.
- Where is the official C++23 spec?
  - https://www.iso.org/standard/83626.html
- Why was this link chosen instead?
  - It is chosen because it is free , unlike the official spec , and is somewhat similar (draft) of C++ 23 spec.
- Is this a helpful reference for learning C++?
   - Not really , it seems very structred draft, clearing doubts using this might not be the best , we can use cppreference.com instead.
- Can the various implementations of C++ compilers be different from the
  C++ standard?
   - No , it should follow C++ standard.
- What are the most widely used and most significant C++ compilers?
  - g++ , Clang
- Where is the equivalent spec for C++26?
   - https://github.com/cplusplus/draft is the ongoing source files available.
- Where do you find the spec for the HTTP protocol?
   - https://www.rfc-editor.org/rfc/rfc9110.html is the latest specifications document.
- What about HTTPS? Is there a spec for that protocol?
  - There is no specific spec , as it is built by HTTP + TLS(Transport layer security).

## Introduction to C++ and Sockets Programming

- Read the code in `src/`
- Are there any bugs in this code? 
  - One thing is if we read  kBufferSize in client and server , char array cannot store '\0' at the end, so increase the size of char array by 1 
  - Also after every read , we have to manually put '\0' after the char array.
- What can you do to identify if there are bugs in the code?
  - Test it with edge cases(mainly testing with different variety/category of testcases) helps.

## Refactoring: Extract Function

- What is different in this code compared to exercise-1?
  - The code is modular in exercise-2 (each part is having its own function call)
- Is this code better or worse than exercise-1?
  - This is better than exercise-1 , as it is easier to read, debug and understand the code. 
- What are the tradeoffs compared to exercise-1?
  - This is good for debugging , understanding , etc , whereas one thing which is bad is , it leads to a higher number of jump instructions at the assembly level, especially when using function calls. 
- Are you able to spot any mistakes or inconsistencies in the changes?
  - No 
## Thinking About Performance

- Does writing code this way have any impact on performance?
  - Not really , though they have a small overhead , with optimised compilers , it does not affect that much.
- What do we mean when we say performance?
  - It means how much efficiently the program runs.
- How do we measure performance in a program?
  - We can use std::chrono::high_resolution_clock::now() to measure high resolution time.

## Play with Git

- There isn't necessarily a single correct answer for how to abstract the 
  code from exercise-1 into functions
- Try different ways to refactor the code from exercise-1 to make it more
  readable.
- Make sure to commit each change as small and self-contained commit
- This will make it easier to revert your code if you need to
- What is `git tag`? How is `git tag` different from `git branch`?
  - git tag is a a fixed marker pointing to a specific commit, whereas branch is a pointer to a moving commit . Tag can't be used to track modifications , it is fixed.
- How can you use `git tag` and `git branch` to make programming easier and
  more fun?
    -  git tag can be used to mark certain versions , bookmark releases, while git branch can be used to test ideas independently without affecting the main branch.

## Learn Basics of Debugging in Your IDE

- How do you enable debug mode in your IDE?
- In debug mode, how do you add a watch?
- In debug mode, how do you add a breakpoint?
- In debug mode, how do you step through code?

### Memory Management and Debug Mode in Your IDE

- How do you see the memory layout of a `std::string` from your IDE debug mode?
- How do you see the memory layout of a struct from your IDE debug mode?