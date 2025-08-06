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
//	Export Utils
void	envp_list_addback(t_envp **list, t_envp *new_node);
void	create_envp_list(t_envp **env_list, char **env);
t_envp	*envp_get_last(t_envp *node);
t_envp	*create_node(char *name, char *content, bool exported);
int		envp_list_size(t_envp *node);
void	bubble_sort(t_envp **arr, int list_size);
void	show_export(t_envp *node);
void	create_envp_var(t_shell *mshell, t_token **token, bool exported);
int		validade_export_name(char *name);
int		has_content(char *name);
t_envp	*find_envp(t_envp *node, char *name);
void	update_export(t_shell *mshell, t_token **token);
void	update_envp_var(t_token **token, t_envp *node);

#endif
