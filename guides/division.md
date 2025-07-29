This is one ideia by chatgpt 

Person A — Core Shell & Parsing

Responsibilities:
 - Main shell loop
    Handle prompt display, reading input, signal handling in main.c and prompt.c.

 - Lexical analysis (lexer)
    Tokenize the input line, manage quotes, metacharacters (lexer.c).

 - Parsing
    Build command structures, detect syntax errors, handle environment variable expansion (parser.c).

 - Signal handling
    Implement global signal variable, setup signal handlers.

Person B — Execution & Built-ins

Responsibilities:
 - Command execution
    Handle execution logic, process forking, pipes, redirections (executor.c, redir.c).

 - Built-in commands
    Implement builtins like echo, cd, pwd, export, unset, env, and exit (builtins/).

 - Environment variable management
    Access and modify environment variables for builtins and expansions.

 - Heredoc implementation

Shared & Collaborative Tasks
 - Makefile, project structure, includess (minishell.h)
    Should be agreed on and maintained collaboratively.

 - Testing
    Both write test cases and verify features.

 - Code style & norm compliance
    Agree on style, review each other’s code.

Person A focuses on input processing and preparing commands, which is mostly sequential and can be tested independently.
Person B focuses on running commands and built-ins, which depends on the parsed command structures.
Minimal overlap but clear integration points: Person A outputs parsed commands; Person B consumes and executes them.
Both have roughly equal workload complexity.
