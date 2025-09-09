#ifndef MINISHELL_H
# define MINISHELL_H

//	C libraries
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
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
# include "safe.h"
# include "lexing.h"
# include "free.h"
# include "inits.h"
# include "rename_later_utils.h"
# include "parsing.h"
# include "built_ins.h"
# include "execute.h"
# include "signals.h"

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

//Error Values
# define NOT_FOUND 127
# define FOUND_NOT_EXEC 126
# define ERROR 1

// Error Texts
# define ERR_QUOTE "Error: Unmatched quotes in input\n"
# define ERR_SYNTAX "Error: Syntax error in command line input\n"
# define ERR_CMD "Error: Command not found\n"
# define ERR_REDIRECT "Error: Invalid redirection syntax\n"
# define ERR_PIPELINE "Error: Invalid pipeline syntax\n"
# define ERR_EXPORT "minishell: export: %s: not a valid identifier\n"
# define DEFINE_X "declare -x %s=\"%s\"\n"
# define ERR_CD_ARGS "minishell: cd: too many arguments\n"
# define ERR_NO_FILE "minishell: %s: No such file or directory\n"
# define ERR_CD_NO_ENVP "minishell: cd: %s is not set\n"
# define ERR_CD_INVALID_OPT "minishell: cd: invalid option\n"
# define ERR_NO_ENVP "Error: No environment variables"
# define ERR_COMPUTER_ERROR "Error: Computer error"
# define ERR_EXIT_NOT_NBR "Error exit: %s: numeric argument required\n"
# define ERR_NO_FLAG_ALLOWED "Error: No flags allowed\n"
# define ERR_PWD "pwd: Error retrieving directory\n"
# define ERR_MEMORY_SHLVL "Memory allocation failed for new shell level"
# define ERR_SHLVLNOT_FOUND "Error: shell level not found\n"
# define ERR_NO_PERMS "minishell: %s: Permission denied\n"

extern int	g_sig;

#endif
