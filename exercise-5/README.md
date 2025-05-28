# Exercise 5

**Update this README with your answers to the questions below.**

## Comparing File Changes

- What's an easy way to identify the changes in source code from one exercise
  to another?

Ans. use this command
```
 diff -u exercise-3/src/tcp_echo_client.cc exercise-4/src/tcp_echo_client.cpp
```
    
## Using Classes

- Here is one way to separate out the code into multiple files
#
- Is this the best way to do it? 

Ans. It depends. Using classes provide better organization and encapsulation, especially as code complexity grows.
#

- What are the advantages and disadvantages?

Ans. Advantages are many, including modularity, abstraction, easy testability and its resusable due to objects. Disadavantage is that in smaller programs, this creates complexity and more lines of code.

## Introduction to Namespace

- There are different ways namespace is being used in this exercise
#
- Which way is better? What are the advantages and disadvantages?

Ans. Using named namespaces is preferred over unnamed ones as it has multiple advantages such as prevention of symbol collisions, improves code organisation and readability also with downsides like code appears more verbose to write something like "network::" everywhere.
#
## Abstracting Code into Classes

- Abstract the client and server logic into a `Client` and `Server` class
- **Note**: You don't have to use the code in this exercise as a starting point
- You can use the code you wrote from previous exercises instead
- How should you divide the code into files?
- What namespace and directory structure should you use? Why?

## Programming Sense of Taste

- How do you judge what makes a particular choice of namespace and directory
  structure? 
- How do you judge what makes a good naming convention or programming style?

## "Senses" in Programming

- Have you ever heard of programmers referring to "code smells"? How can code
  smell?
- What does it mean to have a sense of taste in programming? How can code
  taste?
- Is there an analogue for every sense?
- What other code senses can you think of?
- How many senses do humans have?
- When would you want to see something before you touch it?
- When would you want to touch something before you see it?