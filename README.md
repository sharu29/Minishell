#  Minishell

Minishell is a basic Unix shell implemented in C, built as part of the 42 Prague curriculum. It recreates many features of a real shell such as parsing, command execution, environment variable management, and built-in functions — all within the constraints of the C standard library and POSIX system calls.

---

##  Project Goals

The goal of Minishell is to understand how a shell works behind the scenes — including:
- Input parsing and tokenization
- Handling pipes and redirections
- Executing built-in and external commands
- Managing child processes and signals
- Working within strict memory and error management guidelines

---

##  Features

- Prompt that waits for user input  
- Execute built-in commands: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`  
- Handle environment variables  
- Input/output redirection (`>`, `<`, `>>`)  
- Piping (`|`) between multiple commands  
- Exit status tracking (`$?`)  
- Signal handling (`Ctrl+C`, `Ctrl+D`, etc.)  
- Quote handling (`'` and `"`)

