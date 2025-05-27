# Exercise 3

**Update this README with your answers to the questions below.**

## Re-using Code

- Read the code in `src/tcp_echo_client.cc`
- A new function `check_error()` has been created and `create_socket()` from exercise-2 has been refactored to make use of it
- What are the benefits of writing code in this way?
  - Makes the code more readable, because all error checks are in the format `<condition, error message>`
  - Avoids clutter in the main modules of the program due to a lot of error messages
- Are there any costs to writing code like this?
  - Slightly higher performance overhead, due to copying of the error message from a C-style string literal into an `std::string` every time the function is called
- Apply `check_error` to all the code in `src/`

## Introduction to Compiler Explorer

- Try out the old `create_socket()` and the new `check_error()` and 
  `create_socket()` in [Compiler Explorer](https://godbolt.org) - Interactive 
  tool for exploring how C++ code compiles to assembly
- What is happening here?
  - The old `create_socket()` function had fewer assembly instructions and was much more efficient
  - A copy of the error string had to be allocated on the memory so that it can be passed by value to the function - adds additional time and memory overhead
  - More #of copies between registers, because registers have to be setup appropriately before making a function call to the `check_error()` function, adds additional time overhead
  - Unnecessary computations; for eg, the value of `sock < 0` is computed first, and then we are checking if `test == 1` inside the function, which translates to `(sock < 0) == 1`, which is essentially just `sock < 0`; just one comparison with 0 is enough rather than computing `sock < 0` using the right shift operation and checking whether it's equal to 1 inside the `check_error()` function
  - These inefficienies are barely noticeable when the program is run normally; however, in a setting where every clock cycle matters, this makes a considerable amount of difference in the runtime (the newer version is significantly slower)
- Can you think of any different approaches to this problem?
  - Pass the string by reference to the `check_error()` function
  - Inline the function
- How can you modify your Makefile to generate assembly code instead of compiled code?
  - Compile with `-S` flag
- **Note**: You can save the generated assembly from Compiler Explorer
- **Bonus**: Can you view assembly code using your IDE?
- **Bonus**: How do you see the assembly when you step through each line in
  debugging mode from your IDE?
- [x86 assembly reference](http://ref.x86asm.net/) - Comprehensive reference 
  for x86 assembly language instructions and syntax

## More About Memory Management

- Make sure you have `-fsanitize=address` in both your `CXX_FLAGS` and 
  `LD_FLAGS` in your Makefile
- What do `-fsanitize=address`, `CXX_FLAGS` and `LD_FLAGS` mean?
- With the new tool of the Compiler Explorer, and keeping in mind what you 
  have learned about how to use debug mode
- What happens when you look at a `std::string` using the above methods?
- Where is the text in your `std::string`?
- What is `std::optional`?
- How do you find out the memory layout of a `std::optional`?
- Read https://en.cppreference.com/w/cpp/memory#Smart_pointers - Guide to 
  modern C++ memory management using smart pointers
- Which pointer types are the most important to know about?
- Which smart pointer should you use by default if you can?
- Does changing your optimization level in `CXXFLAGS` from `-O0` to `-O3` have
  any impact on the answers to any of the above questions?

## More Thinking About Performance

- After your experiments with Compiler Explorer, do you have any updates for your answers in exercise-2?
  - In my ex.2 answers, I did mention about a slight performance overhead due to modularizing the code; however, I think the overhead could be more significant in a setting where each and every clock cycle matters

### Bonus: Do Not Watch Now 

- [More about Compiler Explorer](https://www.youtube.com/watch?v=bSkpMdDe4g4) - 
  Deep dive into compiler optimization and assembly analysis
  - Create a struct which contain many different data types
  - Look at the memory layout in the debugger
  - Create a `char` or `uint8_t` pointer to the beginning of the struct, 
    iterate to the end of the struct, printing out the value of each byte in 
    hexadecimal
  - Try accessing different parts of the struct and see in compiler explorer
    what the assembly looks like
  - What happens if you iterate the pointer to outside the bounds of your
    array?
  - Let's say your struct is called `Foo`
  - What is the difference between `std::vector<Foo>` and `std::vector<Foo*>`?
  - What are the tradeoffs between using `std::vector<Foo>` vs 
    `std::vector<Foo*>`? 
  - Give an example where `std::vector<Foo>` is a better choice than 
    `std::vector<Foo*>`
  - Give another example where the opposite is true
  - Can you create `std::vector<Foo&>`? 
  - Can you create `std::vector<std::optional<Foo>>`?
  - What happens if your struct contains another struct?
  - What is the difference between a struct and a class?