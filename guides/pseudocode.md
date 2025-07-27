## 🧠 Global Design

### Global Variable:
  volatile sig_atomic_t g_signal_received
## 🛠️ Main Function

    main():
      initialize_shell_environment()
      set_signal_handlers()
      while true:
        display_prompt()
        line = readline(prompt)
        if line is NULL:
            handle_ctrl_d_exit()
        if line is empty or only whitespace:
            continue
        add_line_to_history(line)
        tokens = lexical_analysis(line)
        if quotes_unbalanced(tokens):
            print_error("Unclosed quotes")
            continue
        commands = parse_tokens(tokens)
        if commands is invalid:
            print_error("Syntax error")
            continue
        execute_commands(commands)
        free_allocated_resources()
## 🧩 Lexical Analysis
    lexical_analysis(line):
      split line into tokens
      preserve quotes
      mark redirection operators (<, >, >>, <<)
      handle metacharacters and whitespace
      return list of tokens
## 🏗️ Parsing
    parse_tokens(tokens):
      identify built-ins vs external commands
      recognize and group redirections
      build command structures:
        - command
        - arguments
        - redirections
        - pipes
      return list of parsed command structures
## 🧪 Execution
    execute_commands(commands):
      if single built-in with no pipes and no redirection:
        execute_builtin_in_parent(commands[0])
      else:
        setup_pipes(commands)
        for each command:
            fork()
            in child:
                setup_redirection()
                if built-in:
                    execute_builtin()
                else:
                    resolve_path_and_execve()
            in parent:
                close_unused_pipe_ends()
        wait_for_all_children()
## 🔁 Built-in Commands
    execute_builtin(cmd):
      if cmd.name == "cd":
        change_directory(cmd.args)
      else if cmd.name == "echo":
        print_args(cmd.args)
      else if cmd.name == "pwd":
        print_working_directory()
      else if cmd.name == "export":
        set_environment_variable(cmd.args)
      else if cmd.name == "unset":
        unset_environment_variable(cmd.args)
      else if cmd.name == "env":
        print_environment()
      else if cmd.name == "exit":
        exit_shell(cmd.args)
## 🔁 Redirections
    setup_redirection(cmd):
      for redirection in cmd.redirections:
        if redirection.type == '>':
            open file for writing (truncate)
            dup2 to stdout
        else if redirection.type == '>>':
            open file for appending
            dup2 to stdout
        else if redirection.type == '<':
            open file for reading
            dup2 to stdin
        else if redirection.type == '<<':
            handle_heredoc(delimiter)
## 📌 Signals
    set_signal_handlers():
      if in interactive mode:
        handle SIGINT (ctrl-C): 
            set g_signal_received
            write new prompt
        handle SIGQUIT (ctrl-\): ignore
        handle EOF (ctrl-D): handled in main loop
## 🔍 Environment Expansion
    expand_variables(tokens):
      for token in tokens:
        if contains $VAR or $?:
            replace with actual value
    return tokens
## 📁 Utility Functions
    resolve_path_and_execve():
      if command contains /:
        try execve(command, args)
      else:
        search command in PATH
        try execve with full path

    add_line_to_history(line):
      use readline’s add_history()

    free_allocated_resources():
    free tokens, command structures, redirection data, etc.
