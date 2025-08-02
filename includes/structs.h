#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token
{
	char			*name;
	int				type;
	bool			has_quote;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct s_cmd
{
	char			*cmd_name;
	char			*flags;
	char			*args;
}		t_cmd;

typedef struct s_shell
{
	char			*rd_l;
	char			**cmd_line;
	char			**env_var;
	char			curr_wd[PATH_MAX];
	char			*fake_cwd;
	int				tokens_size;
	int				num_pipes;
	bool			has_pipes;
	bool			closed_pipe;
	bool			is_running;
}		t_shell;

#endif
