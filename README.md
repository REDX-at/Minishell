# Minishell - 1337 (42 Network)

![Dining Philosophers](https://github.com/REDX-at/Minishell/blob/master/images/minishell%2042.png)

Minishell is a project focused on creating a minimalistic Unix shell. The objective is to implement a basic shell that can interpret and execute commands, handle pipes, and manage process execution using system calls.

## Introduction
The Minishell project challenges students to build a simplified Unix shell from scratch. This involves parsing user input, executing commands, and managing processes while understanding the core functionalities of a shell environment.

## Key Concepts
### 1. Command Parsing
Implement a parser that interprets user input and breaks it down into commands and arguments. Handle different types of commands, including those with pipes and redirection.

### 2. Process Management
Use system calls like fork, execve, and wait to manage the execution of commands. Create child processes for command execution and handle process termination.

### 3. Pipes and Redirection
Implement support for pipes to connect multiple commands, allowing for the output of one command to be used as the input for another. Handle input and output redirection to manage file I/O.

### 4. Signal Handling
Manage signals, such as SIGINT and SIGQUIT, to ensure the shell handles interruptions and terminations gracefully. Implement signal handlers to manage user interruptions.

### 5. Error Handling
Ensure robust error handling for invalid commands, failed process creation, and other potential issues. Provide informative error messages to help users understand and resolve problems.

### Features
Command Execution: Parse and execute commands entered by the user.
Pipe Management: Connect commands using pipes to facilitate complex command sequences.
Redirection: Handle input and output redirection to and from files.
Signal Handling: Implement signal handling for interruptions and terminations.
### Contact
For any questions or feedback, feel free to reach out to me at taoussi.aimen@gmail.com or visit my GitHub profile at GitHub.

