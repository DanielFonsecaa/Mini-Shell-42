#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token
{
	char			*name;
	int				type;
	bool			has_quote;
	bool			is_pipe;
	bool			last_pipe;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct s_cmd
{
	char			*name;
//	char			**flags;
	char			**args;
}		t_cmd;

typedef struct s_envp
{
	char			*name;
	char			*content;
	bool			exported;
	struct s_envp	*next;
}		t_envp;

typedef struct s_shell
{
	char			*rd_l;
	char			**cmd_line;
	char			**env_var;
	char			curr_wd[PATH_MAX];
	char			*fake_cwd;
	char			**exec_command;
	int				num_commands;
	int				tokens_size;
	int				num_pipes;
	int				num_redirecs;
	int				num_heredoc;
	int				fd[2];
	int				*heredoc_fd;
	int				**pipes;
	int				exit_code;
	bool			has_pipes;
	bool			has_redirect;
	bool			closed_pipe;
	bool			is_running;
	t_envp			*env_list;
	t_cmd			**command;
	pid_t			*pids;
}		t_shell;

#endif
