/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:36:50 by npederen          #+#    #+#             */
/*   Updated: 2025/02/03 17:36:50 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include "printf/libft/libft.h"
# include "printf/ft_printf.h"

void	is_server_ready(void);
void	send_end_signal(int s_pid);
void	send_signal(int s_pid, char *str);
void	handle_signal_client(int signum);
int		check_usr_input(int narg, int s_pid, char c);
char	*ft_strjoinchar(char *s1, char carac);
void	handle_signal(int signum, siginfo_t *info, void *data);

#endif