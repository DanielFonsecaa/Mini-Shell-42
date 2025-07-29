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

//	C libraries
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
//	Custom libs
# include "../lib/libft/libft/libft.h"

//	Custom headers
# include "structs.h"
# include "utils.h"
# include "lexing.h"

#endif
