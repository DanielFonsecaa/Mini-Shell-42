#ifndef PARSING_H
# define PARSING_H

//		Utils
int		quote_checker(char *rd_l);
int		check_pipeline(t_token **token);
int		check_redir_type(t_token *temp);
void	pipe_count(t_shell *mshell, t_token **token);
int     count_type_till_pipe(t_token *token, int type);
void    add_flag_to_cmd(t_token **token, t_cmd **command);
void    add_arg_to_cmd(t_token **token, t_cmd **command);

//		Parsing
int		parsing(t_shell *mshell, t_token **token);
t_cmd    **set_cmd_arr(t_shell *mshell, t_token **token);

//		Syntax Checks
int		syntax_error(t_shell *mshell, t_token **token);
int	    check_infile(t_token *token);

#endif
