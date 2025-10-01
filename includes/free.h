/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:38:19 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/01 15:38:19 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

//Main free
void	free_all(t_shell *mshell, t_token **token);
void	handle_error_shell(t_shell *mshell, t_token **token);
void	handle_child_free(t_shell *mshell, t_token **token, char *path);
void	free_heredoc_child(t_shell *mshell, t_token **token);

//free data
void	free_list(t_token **token);
void	free_envp_list(t_shell *mshell);
void	free_strs(char *name, char *content);
void	free_arr(char **arr);
void	free_cmd_struct(t_shell *mshell);
void	free_heredoc(t_shell *mshell);

// free pipes and fds
void	close_fds(int **pipes, int num_pipes, int *fd);
void	cleanup_pipes(int **pipes, int num_pipes, t_shell *mshell);

#endif
