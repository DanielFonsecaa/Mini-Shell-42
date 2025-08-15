#ifndef MINISHELL_H
# define MINISHELL_H

// Type definitions
# define CMD 1
# define ARG 2
# define INFILE 3
# define OUTFILE 4
# define PIPE 5
# define HERE 6
# define FLAG 7
# define TFILE 8
# define APPEND 9
# define PATH_MAX 4096

// Error Texts
# define ERR_MALLOC "Error: Memory allocation failed\n"
# define ERR_QUOTE "Error: Unmatched quotes in input\n"
# define ERR_SYNTAX "Error: Syntax error in command line input\n"
# define ERR_FILE "Error: File not found or inaccessible\n"
# define ERR_CMD "Error: Command not found\n"
# define ERR_REDIRECT "Error: Invalid redirection syntax\n"
# define ERR_PIPELINE "Error: Invalid pipeline syntax\n"
# define ERR_UNEXPECTED "Error: Unexpected token in command line input\n"
# define ERR_INVALID "Error: Invalid command or argument\n"
# define ERR_SIGNAL "Error: Interrupted by signal\n"
# define ERR_EXEC "Error: Execution failed\n"
# define ERR_ENV "Error: Environment variable not found\n"

//	C libraries
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signals.h>
# include <stdbool.h>
# include <stddef.h>
# include <unistd.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>

//	Custom libs
# include "../libft/libft/libft.h"

//	Custom headers
# include "structs.h"
# include "utils.h"
# include "lexing.h"
# include "free.h"
# include "inits.h"
# include "parsing.h"
# include "built_ins.h"
# include "execute.h"
# include "signals.h"

#endif
