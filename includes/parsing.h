#ifndef PARSING_H
# define PARSING_H

//		Utils
int		quote_checker(char *rd_l);
void	pipe_count(t_shell *mshell, t_token **token);
int		check_pipeline(t_token **token);
int		check_redir_type(t_token *temp);

//		Parsing
int		parsing(t_shell *mshell, t_token **token);

//		Syntax Checks
int		syntax_error(t_shell *mshell, t_token **token);

#endif
