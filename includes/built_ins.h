/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:26:39 by dda-fons          #+#    #+#             */
/*   Updated: 2025/08/12 18:23:10 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

// Built ins handler
void	handle_pwd(t_shell *mshell, t_token **token);
void	handle_env(t_shell *mshell);
void	handle_exit(t_shell *mshell, t_token **token);
void	handle_export(t_shell *mshell, t_token **token);
void	handle_cd(t_shell *mshell, t_token **token);
void	handle_unset(t_shell *mshell, t_token **token);

// Utils
int		is_built_in(t_token **token);
int		verify_num(char *value);
int		has_content(char *name);
int		validade_export_name(char *name);

//	Export Utils
void	bubble_sort(t_envp **arr, int list_size);
void	show_export(t_envp *node);
void	update_export(t_shell *mshell, t_token **token);
void	update_envp_var(char *name, t_envp *node);
void	create_envp_list(t_envp **env_list, char **env);
void	create_envp_var(t_shell *mshell, t_token **token, bool exported);
void	envp_list_addback(t_envp **list, t_envp *new_node);
int		envp_list_size(t_envp *node);
t_envp	*create_node(char *name, char *content, bool exported);
t_envp	*find_envp(t_envp *node, char *name);
t_envp	*envp_get_last(t_envp *node);

// CD Utils
void	change_dir(t_shell *mshell, t_token **token);
void	cd_to_key(t_shell *mshell, char *key);
int		cd_syntax(t_shell *mshell, t_token **token);
void	update_envp_with_string(t_shell *mshell, char *key, char *cwd);

// Unset UTils
void	remove_envp_var(t_envp *head, t_envp *node);

#endif
