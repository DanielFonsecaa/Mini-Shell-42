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

- [ ] All source files are .c, .h, and a Makefile only
- [ ] The program is named minishell
- [ ] The Makefile has these rules: NAME, all, clean, fclean, re
- [ ] Uses only authorized functions from the subject	
- [ ] Uses only one global variable for signal handling	

## 🛠️ Core Features

### 🔹 Basic Shell Loop

* [ ] Displays a prompt
* [ ] Reads input using `readline()`
* [ ] Adds command line to history with `add_history()`
* [ ] Handles `Ctrl-C`, `Ctrl-D`, `Ctrl-\` like bash

### 🔹 Parsing

* [ ] Handles unquoted and quoted words correctly
* [ ] Supports `'` (single quotes, no expansion inside)
* [ ] Supports `"` (double quotes, with `$` expansion inside)
* [ ] Detects and reports unclosed quotes
* [ ] Tokenizes metacharacters: `<`, `>`, `<<`, `>>`, `|`
* [ ] Expands environment variables (`$VAR`)
* [ ] Expands `$?` with last exit status

### 🔹 Execution

* [ ] Resolves executables using `$PATH`
* [ ] Executes relative or absolute paths
* [ ] Supports command chaining with pipes (`|`)
* [ ] Supports redirections: `<`, `>`, `>>`, `<<`
* [ ] Implements heredoc with custom delimiter (no history)
* [ ] Forks properly and waits for all children


## 🔁 Built-in Commands

### Each built-in: implementation and edge-case testing

* [ ] `echo [-n]` – implemented
* [ ] `echo [-n]` – edge cases tested
* [ ] `cd [path]` – implemented
* [ ] `cd [path]` – edge cases tested
* [ ] `pwd` – implemented
* [ ] `pwd` – edge cases tested
* [ ] `export` – implemented
* [ ] `export` – edge cases tested
* [ ] `unset` – implemented
* [ ] `unset` – edge cases tested
* [ ] `env` – implemented
* [ ] `env` – edge cases tested
* [ ] `exit` – implemented
* [ ] `exit` – edge cases tested


## 🧠 Signal Handling

* [ ] `SIGINT` (`Ctrl-C`) displays new prompt (interactive)
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

* [ ] Modular code structure
* [ ] Functions are short and well-named
* [ ] No memory leaks (`valgrind ./minishell`)
* [ ] No file descriptor leaks
* [ ] Proper error handling and return values
* [ ] No use of forbidden features (like semicolons or backslashes)
