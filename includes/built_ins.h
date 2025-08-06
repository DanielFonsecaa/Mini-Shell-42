#ifndef BUILT_INS_H
# define BUILT_INS_H

// Built ins handler
void	handle_pwd(t_shell *mshell, t_token **token);
void	handle_env(t_shell *mshell);
void	handle_exit(t_shell *mshell, t_token **token);
void	handle_export(t_shell *mshell, t_token **token);

// Utils
int		is_built_in(t_token **token);
int		verify_num(char *value);
void	free_envp_content(char *name, char *content);
void	envp_list_addback(t_envp *list, t_envp *new_node);
void	create_envp_list(t_envp *env_list, char **env);
void	print_list2(t_envp *node);
t_envp	*envp_get_last(t_envp *node);
t_envp	*create_node(char *name, char *content);

#endif
