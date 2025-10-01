# Mini-Shell 42
<!--div>

<img width="150" height="150" alt="minishelle" src="https://github.com/user-attachments/assets/da3ca75d-8424-4fc2-a581-66f60fca2c5b" />
</div-->
**Mini-Shell** is a project completed as part of the 42 School curriculum. The goal is to recreate a minimal UNIX shell that behaves similarly to Bash, implementing parsing, execution, pipelines, redirections, and built-in commands, while managing environment variables and handling signals.

> _"The objective of this project is to create a simple shell, reproducing the behavior of Bash as closely as possible, with a focus on understanding how a shell works internally."_

---
[![Co-author: DanielFonsecaa](https://img.shields.io/badge/Co--author-DanielFonsecaa-blue)](https://github.com/DanielFonsecaa)
[![Co-author: NukyYuki](https://img.shields.io/badge/Co--author-NukyYuki-pink)](https://github.com/NukyYuki)

<!--div>

| Grade                                                             | Evaluation Information           |
| :---------------------------------------------------------------- | :------------------------------- |
| <img src="https://img.shields.io/badge/100%20%2F%20100%20%E2%98%85-sucess"/>  | `3 peers` `1 hour` |
</div-->
---

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Builtins Implemented](#builtins-implemented)
- [Parsing & Execution](#parsing--execution)
- [Signals & Error Handling](#signals--error-handling)
- [Bonus / Extra Features](#bonus--extra-features)
- [Known Issues](#known-issues)
- [Authors](#authors)
- [License](#license)

---

## Features

- Prompt display in interactive mode
- Command line parsing with:
  - Quotes (`single` and `double`)
  - Escapes
  - Environment variable expansion
- Execution of simple commands and pipelines (`|`)
- Support for redirections (`>`, `>>`, `<`, `<<`)
- Built-in command support (see below)
- Handling of environment variables (`export`, `$VAR`, etc.)
- Error handling (syntax, execution, etc.)
- Signal handling for `SIGINT` (Ctrl+C), `SIGQUIT` (Ctrl+\), heredoc signals
- Exit status management
- No memory leaks (tested with Valgrind)

---

## Installation

### Requirements

- Unix-based system (Linux/macOS)
- GCC compiler (or compatible)
- `make`
- [readline](https://tiswww.case.edu/php/chet/readline/rltop.html) library (`libreadline-dev` on Ubuntu)

### Build

```sh
git clone https://github.com/DanielFonsecaa/Mini-Shell-42.git
cd Mini-Shell-42
make
```

The executable will be created as `./minishell`.

---

## Usage

Start the shell by running:

```sh
./minishell
```

You will see a prompt similar to:

```
minishell$ 
```

Type commands as you would in Bash:

- Execute binaries:
  ```
  minishell$ ls -la /tmp
  ```
- Use pipes:
  ```
  minishell$ ls | grep src
  ```
- Use redirections:
  ```
  minishell$ echo hello > file.txt
  minishell$ cat < file.txt
  ```
- Use environment variables:
  ```
  minishell$ export MYVAR=42
  minishell$ echo $MYVAR
  ```

Exit with `exit`, `Ctrl+D`, or by typing `exit 42` (with the desired code).

---

Key components:

- **Parsing**: Lexical analysis, tokenization, syntax parsing, expansions
- **Execution**: Built-in/execve, pipelines, redirections
- **Env**: Environment variables management
- **Signals**: Signal handlers for interactive mode
- **Utils**: Helper functions

---

## Builtins Implemented

The following built-in shell commands are implemented:

| Built-in   | Description                                    |
|------------|------------------------------------------------|
| `echo`     | Print arguments to stdout                      |
| `cd`       | Change current directory                       |
| `pwd`      | Print working directory                        |
| `export`   | Set environment variables                      |
| `unset`    | Remove environment variables                   |
| `env`      | Display environment variables                  |
| `exit`     | Exit the shell                                 |

---

## Parsing & Execution

**Lexer**:  
  - Scans and tokenizes user input into meaningful tokens, correctly handling:
    - Single and double quotes
    - Escape characters (backslashes)
    - Special shell symbols (|, >, <, etc.)
    - Whitespace and delimiters

**Parser**:  
  - Constructs an internal representation (such as an Abstract Syntax Tree) from the tokenized input, with support for:
    - Command grouping (sequences and compound commands)
    - Pipelines (`|`) connecting commands
    - Input/output redirections (`>`, `>>`, `<`, `<<`)
    - Environment variable expansion (e.g., `$HOME`, `$?`)
    - Comprehensive syntax error detection and reporting

**Executor**:  
  - Executes parsed commands by:
    - Running built-in commands internally without spawning new processes
    - Creating child processes with `fork` and executing external programs with `execve`
    - Establishing pipes and setting up file descriptors for redirections
    - Managing file creation (e.g., truncation, appending, heredoc files) and verifying file access permissions
    - Cleaning up resources and restoring shell state after execution

---

## Signals & Error Handling

- `SIGINT` (Ctrl+C): Interrupts current command or clears prompt
- `SIGQUIT` (Ctrl+\): Ignored in interactive mode, handled in child
- Heredoc: Handles `SIGINT` to safely interrupt input
- Syntax errors: Informative messages on invalid input
- Exit codes: Consistent with Bash where possible

---

## Bonus / Extra Features

- Support for multiple consecutive pipes and redirections
- Heredoc (`<<`) with variable expansion
- Proper file descriptor management
- Memory leak checks (Valgrind clean)
- History navigation (if readline is available)

---

## Known Issues

- Wildcard expansion (`*`) not implemented
- Wildcard (`&& || \`) not implemented
- Some advanced Bash features (subshells, process substitution, etc.) are out of scope
- May behave differently from Bash in edge cases (`export` without arguments, etc.)

---

## Authors

- [DanielFonsecaa](https://github.com/DanielFonsecaa)
- [NukyYuki](https://github.com/NukyYuki)
