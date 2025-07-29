#ifndef UTILS_H
# define UTILS_H

void	*safe_malloc(size_t size);
void	*safe_calloc(int nmemb, size_t size);
void	set_bool(bool *val, bool change);

//lex utils
int 	increment_token(char line);
int 	is_meta_char(char c);

#endif
