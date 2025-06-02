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
  - I divided the code into separate files: `client.h`/`client.cc` for the `Client` class and `server.h`/`server.cc` for the `Server` class. Each class has its own header and implementation file.
  - I placed these files in a `client/` directory, matching the namespace `tt::chat::client`. This keeps the directory structure consistent with the namespace, making it easier to locate files and understand the project organization.
  - This approach improves maintainability and scalability, especially as the project grows.
- What namespace and directory structure should you use? Why?
  - I used the `tt::chat::client` and `tt::chat::server` namespaces for the `Client` and `Server` classes, respectively. The files are organized into `client/` and `server/` directories, each containing their own header and implementation files. This mirrors the namespace hierarchy in the directory structure, making it intuitive to find and manage code. It also helps prevent naming conflicts and keeps related code grouped together, which is especially helpful as the project grows.

## Programming Sense of Taste

- How do you judge what makes a particular choice of namespace and directory
  structure? 
  - I think a good namespace and directory structure should make it easy to find, understand, and maintain code. If the structure matches how the code is organized logically (for example, by feature or component), it's easier to work with.
- How do you judge what makes a good naming convention or programming style?
  -  A good naming convention or style should be clear, consistent, and descriptive, so that anyone reading the code can quickly understand what things are and how they relate. I try to follow common conventions and keep things simple and readable.

## "Senses" in Programming

- Have you ever heard of programmers referring to "code smells"? How can code
  smell?
  - Code smells are patterns that suggest deeper problms like duplicate code, long methods, too many parameters.
- What does it mean to have a sense of taste in programming? How can code
  taste?
  - It's about appreciating elegant solutions and clean design
  - Good code "tastes" clean and straightforward
- Is there an analogue for every sense?
  - Yes, we see code, feel its structure, hear about issues.
- What other code senses can you think of?
  - Code flow (touch)
  - Code clarity (sight)
  - Code complexity (taste)
  - Code patterns (hearing patterns)
- How many senses do humans have?
  - The classic five, plus balance, temperature, and more
- When would you want to see something before you touch it?
- When would you want to touch something before you see it?