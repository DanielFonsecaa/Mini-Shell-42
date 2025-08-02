#ifndef PARSING_H
# define PARSING_H

void	pipe_count(t_shell *mshell, t_token **token);
void	parsing(t_shell *mshell, t_token **token);
//		Syntax Checks
int	quote_checker(char *rd_l);
int	syntax_error(t_shell *mshell, t_token **token);

#endif
