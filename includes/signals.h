/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mipinhei <mipinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:21:02 by mipinhei          #+#    #+#             */
/*   Updated: 2025/10/01 15:21:03 by mipinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	handle_signal(void);
void	handle_ctrl_c(int sig);
void	handle_ctrl_c_child(int sig);
void	handle_child(void);
void	handle_quit_child(int sig);
void	block_parent_signals(void);
void	restore_parent_signals(void);
void	handle_heredoc_signal(int sig);
void	handle_sigpipe(int sig);

#endif
