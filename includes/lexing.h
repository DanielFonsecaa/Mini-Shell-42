#ifndef LEXING_H
# define LEXING_H

// lex related
int		tokenize(char *rd_l, t_token **token);
void	ft_first_token(t_token **token, char *line, int size);
void	set_t_type(t_token **token);
void	type_file(t_token **token);

//	list handling
int		token_list_size(t_token *token);
void	token_addback(t_token **token, t_token *new_token);
t_token	*ft_newtoken(char *content);
t_token	*token_lst_last(t_token *token);

// lex utils
int		is_meta_char(char c);
int		has_quote(char *str);
int		skip_inside_quotes(char *rd_l, int *j, char c);
void	print_list(t_token **token);

#endif
