#ifndef LEXING_H
# define LEXING_H

void	split_rdline(t_shell *mshell, t_token **token);
void	tokenize(char *rd_l, t_token **token);
//	list handling
t_token	*ft_newtoken(char *content);
void	token_addback(t_token **token, t_token *new_token);
t_token *token_lst_last(t_token *token);
int	token_list_size(t_token *token);

#endif
