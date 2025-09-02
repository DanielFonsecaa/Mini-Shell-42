#ifndef PARSING_H
# define PARSING_H

//		Parsing
int		parsing(t_shell *mshell, t_token **token);

//      Expansion
void	expansion(t_shell *mshell, t_token **token);
char	*append_exit_code(t_shell *mshell, char *new_str, int *i);
char	*append_content(t_shell *mshell, t_token **token, char *str, int *i);
char	*append_letter(t_token **token, char *old_str, int *i);
char	*append_letter_unquoted(t_token *token, char *new_str, int *i);
void	expand_quoted_token(t_shell *mshell, t_token *token);
void	expand_unquoted(t_shell *mshell, t_token **current, t_token **head);
char	*expand_token_content(t_shell *mshell, t_token *token);

//		Syntax Checks
int		syntax_error(t_shell *mshell, t_token **token);
int		quote_checker(char *rd_l);
int		check_pipeline(t_token **token);
int		check_redir_type(t_token *temp);
int		check_infile(t_token *token);
int		check_perms(t_shell *mshell, t_token *token);

#endif
