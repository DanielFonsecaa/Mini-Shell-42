#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_token
{
	char	*name;
	int		type;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct	s_cmd
{
	char	*cmd_name;
	char	*flags;
	char	*args;
}		t_cmd;

typedef struct s_shell
{
	char	*rd_l;
	bool	is_running;
	char	**cmd_line;
}		t_shell;

#endif
