#ifndef PARSING_H
# define PARSING_H

//		Parsing
int		parsing(t_shell *mshell, t_token **token);

//      Expansion
void	expansion(t_shell *mshell, t_token **token);

//		Syntax Checks
int		syntax_error(t_shell *mshell, t_token **token);
int		quote_checker(char *rd_l);
int		check_pipeline(t_token **token);
int		check_redir_type(t_token *temp);
int		check_infile(t_token *token);

#endif
