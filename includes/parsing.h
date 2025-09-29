#ifndef PARSING_H
# define PARSING_H

//		Parsing
int		parsing(t_shell *mshell, t_token **token);

//      Expansion
char	*append_exit_code(t_shell *mshell, char *new_str, int *i);
char	*append_content(t_shell *mshell, t_token **token, char *str, int *i);
char	*append_letter(t_token **token, char *old_str, int *i);
char	*append_letter_unquoted(t_token *token, char *new_str, int *i);
char	*expand_token_content(t_shell *mshell, t_token *token);
void	expansion(t_shell *mshell, t_token **token);
void	expand_quoted_token(t_shell *mshell, t_token *token);
void	expand_unquoted(t_shell *mshell, t_token **current, t_token **head);
void	add_split_tokens(t_token **current, t_token *next, char **arr);
void	expand_inside_quotes(t_token *token, t_shell *msh, char **str, int *i);
void	expand_export_assignment(t_shell *mshell, t_token *token);
int		append_envar_val(t_shell *ms, t_token **tok, char **str, int start);
int		is_export_assignment(t_token *current, t_token **head);
int		is_special_shell_var(char c);
int		handle_special_var_case(t_token **token, char **str, int *i, int star);
int		try_expand_tilde(t_shell *mshell, t_token *current);
int		remove_if_empty(char *exp, char **arr, t_token **curr, t_token **head);

//		Syntax Checks
int		syntax_error(t_shell *mshell, t_token **token);
int		quote_checker(char *rd_l);
int		check_pipeline(t_token **token);
int		check_redir_type(t_token *temp);
int		check_infile(t_token *token);
int		check_perms(t_shell *mshell, t_token *token);
int		helper_check_perms(char *token_name, char *path_name);

#endif
