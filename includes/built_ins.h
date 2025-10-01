/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:41:25 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/01 15:41:25 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

// Built ins handlers
void	handle_pwd(t_shell *mshell, t_token **token, int fd);
void	handle_env(t_shell *mshell, int fd, t_token **token);
void	handle_exit(t_shell *mshell, t_token **token);
void	handle_export(t_shell *mshell, t_token **token, int fd);
void	handle_cd(t_shell *mshell, t_token **token);
void	handle_unset(t_shell *mshell, t_token **token);
void	handle_echo(t_shell *mshell, int fd);

// Utils
int		is_built_in(t_token **token);
int		verify_num(char *value);
int		has_content(char *name);
int		validade_export_name(char *name);

//	Export Utils
void	bubble_sort(t_envp **arr, int list_size);
void	show_export(t_shell *mshell, t_envp *node, int fd);
void	update_export(t_shell *mshell, t_token **token, int *flag);
void	update_envp_var(char *name, t_envp *node);
void	append_envp_var(char *name, t_envp *node);
void	create_envp_list(t_envp **env_list, char **env);
void	create_envp_var(t_shell *mshell, t_token **token, bool exported);
void	envp_list_addback(t_envp **list, t_envp *new_node);
char	*escape_export_content(const char *content);
char	*skip_quotes(char *str);
int		envp_list_size(t_envp *node);
t_envp	*create_node(char *name, char *content, bool exported);
t_envp	*find_envp(t_envp *node, char *name);
t_envp	*envp_get_last(t_envp *node);

// CD Utils
void	change_dir(t_shell *mshell, t_token **token);
void	cd_to_key(t_shell *mshell, char *key);
int		cd_syntax(t_shell *mshell, t_token **token);
void	update_envp_with_string(t_shell *mshell, char *key, char *cwd);

// Unset Utils
void	remove_envp_var(t_envp **head, t_envp *node);

// Echo Utils
t_token	**get_args(t_token **token);
void	print_echo(char **arr, bool flag, int i, int fd);
int		valid_n(char *str);
int		handle_n(char **command_arr, int *i);
char	which_quote(char *str);

//env
int		check_for_flags(t_shell *mshell);
int		check_for_args(t_shell *mshell, t_token **token);

#endif