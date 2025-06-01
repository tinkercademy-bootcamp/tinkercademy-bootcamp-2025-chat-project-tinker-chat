# Exercise 5

**Update this README with your answers to the questions below.**

## Comparing File Changes

- What's an easy way to identify the changes in source code from one exercise
  to another?
  - Use diff, git diff or meld. You can also use VS code's built-in diff viewer.
    
## Using Classes

- Here is one way to separate out the code into multiple files
- Is this the best way to do it? 
  - It's a very good way, but what's best depends upon the size and complexity of the project.
- What are the advantages and disadvantages?
  - Advantages: Better organization, easier testing, cleaner code structure, reusability
  - Disadvantages: More files to manage, slight overhead for small projects, need to think about dependencies

## Introduction to Namespace

- There are different ways namespace is being used in this exercise
- Which way is better? What are the advantages and disadvantages?
  - Using nested namespaces (like tt::chat::net in our case) helps organize code hierarchically
  - Triple-nested namespace provides clear separation: tt (project) -> chat (module) -> net (component)
  - Flat namespaces would be simpler but could lead to naming conflicts
  - I find nested namespaces more maintainable for structured projects like ours

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