```plaintext
minishell/
├── src/
│   ├── main.c                # Entry point of the shell
│   ├── prompt.c              # Prompt display and input handling
│   ├── lexer.c               # Lexical analysis: tokenizing input
│   ├── parser.c              # Syntax parsing and command structure creation
│   ├── executor.c            # Command execution logic
│   ├── redir.c               # Input/output redirection handling
│   └── builtins/             # Built-in shell command implementations
│       ├── echo.c
│       ├── cd.c
│       └── ...               # Other builtins (export, unset, etc.)
├── includes/
│   └── minishell.h           # Project-wide header and structure definitions
├── libft/                    # Your custom libft library
├── Makefile                  # Build script with required rules
└── README.md
```

## 📦 Submission Requirements

### 🔹Task	Done

- [x] All source files are .c, .h, and a Makefile only
- [x] The program is named minishell
- [x] The Makefile has these rules: NAME, all, clean, fclean, re
- [x] Uses only authorized functions from the subject	
- [x] Uses only one global variable for signal handling	

## 🛠️ Core Features

### 🔹 Basic Shell Loop

* [x] Displays a prompt
* [x] Reads input using `readline()`
* [x] Adds command line to history with `add_history()`
* [ ] Handles `Ctrl-C`, `Ctrl-D`, `Ctrl-\` like bash

### 🔹 Parsing

* [ ] Handles unquoted and quoted words correctly
* [ ] Supports `'` (single quotes, no expansion inside)
* [ ] Supports `"` (double quotes, with `$` expansion inside)
* [x] Detects and reports unclosed quotes
* [x] Tokenizes metacharacters: `<`, `>`, `<<`, `>>`, `|`
* [ ] Expands environment variables (`$VAR`)
* [ ] Expands `$?` with last exit status

### 🔹 Execution

* [ ] Resolves executables using `$PATH`
* [x] Executes relative or absolute paths
* [x] Supports command chaining with pipes (`|`)
* [ ] Supports redirections: `<`, `>`, `>>`, `<<`
* [ ] Implements heredoc with custom delimiter (no history)
* [x] Forks properly and waits for all children


## 🔁 Built-in Commands

### Each built-in: implementation and edge-case testing

* [x] `echo [-n]` – implemented
* [ ] `echo [-n]` – edge cases tested
* [x] `cd [path]` – implemented
* [ ] `cd [path]` – edge cases tested
* [x] `pwd` – implemented
* [ ] `pwd` – edge cases tested
* [x] `export` – implemented
* [ ] `export` – edge cases tested
* [x] `unset` – implemented
* [ ] `unset` – edge cases tested
* [x] `env` – implemented
* [ ] `env` – edge cases tested
* [x] `exit` – implemented
* [ ] `exit` – edge cases tested


## 🧠 Signal Handling

* [x] `SIGINT` (`Ctrl-C`) displays new prompt (interactive)
* [ ] `SIGQUIT` (`Ctrl-\`) does nothing
* [ ] `Ctrl-D` exits the shell
* [ ] Signal behavior matches bash closely


## 🧪 Testing

* [ ] Single commands
* [ ] Commands with redirections
* [ ] Commands with pipes
* [ ] Quotes and nested quotes
* [ ] Invalid syntax (e.g., `|`, `>`, `<<` alone)
* [ ] Environment variable expansion
* [ ] Return value (`$?`) correctness
* [ ] Built-ins in pipelines (e.g., `echo test | cat`)
* [ ] Heredocs with signals (interrupt heredoc with `Ctrl-C`)


## 🧹 Code Quality & Project Hygiene

* [x] Modular code structure
* [x] Functions are short and well-named
* [x] No memory leaks (`valgrind ./minishell`)
* [x] No file descriptor leaks
* [x] Proper error handling and return values
* [x] No use of forbidden features (like semicolons or backslashes)
