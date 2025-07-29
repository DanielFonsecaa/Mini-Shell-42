#ifndef MINISHELL_H
# define MINISHELL_H

// Type definitions
# define CMD 1
# define ARG 2
# define REDIR 3
# define PIPE 4
# define HERE 5
# define OPTS 6

//	C libraries
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>

//	Custom libs
# include "../lib/libft/libft/libft.h"

//	Custom headers
# include "structs.h"
# include "utils.h"

#endif
