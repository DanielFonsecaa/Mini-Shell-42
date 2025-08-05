#ifndef LEXING_H
# define LEXING_H

// lex related
void	tokenize(char *rd_l, t_token **token);
void	ft_first_token(t_token **token, char *line, int size);
void	set_t_type(t_token **token);
void	type_file(t_token **token);

//	list handling
t_token	*ft_newtoken(char *content);
void	token_addback(t_token **token, t_token *new_token);
t_token	*token_lst_last(t_token *token);
int		token_list_size(t_token *token);

// lex utils
int		is_meta_char(char c);
int		has_quote(char *str);
void	print_list(t_token **token);
int		count_quote_content(char *rd_l, int *j, char c);

#endif
