/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:36:58 by npederen          #+#    #+#             */
/*   Updated: 2025/02/03 17:36:58 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_isready = 0;

void	is_server_ready(void)
{
	int	i;

	i = 1000;
	while (!g_isready && i-- > 0)
		usleep(100);
	if (i == 0)
	{
		ft_printf("Server is not ready\n");
		exit(1);
	}
	g_isready = 0;
}

void	send_end_signal(int s_pid)
{
	int	i;

	i = 8;
	while (i-- > 0)
	{
		kill(s_pid, SIGUSR1);
		is_server_ready();
	}
}

void	send_signal(int s_pid, char *str)
{
	int				i;
	int				j;
	unsigned char	bit;

	j = 0;
	bit = 0;
	while (str[j])
	{
		i = 8;
		while (i-- > 0)
		{
			bit = ((str[j] >> i) & 1);
			if (bit == 0)
				kill(s_pid, SIGUSR1);
			else if (bit == 1)
				kill(s_pid, SIGUSR2);
			is_server_ready();
		}
		j++;
	}
	send_end_signal(s_pid);
}

void	handle_signal_client(int signum)
{
	if (signum == SIGUSR2)
		g_isready = 1;
	else if (signum == SIGUSR1)
		ft_printf("The server got your message.\n");
	else
	{
		ft_putstr_fd("The signal is not supported.", 1);
		exit(1);
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	signalusr;
	int					s_pid;

	if (argc != 3)
	{
		ft_printf("Error !, follow example: ./client <s_pid> <message>\n");
		return (0);
	}
	if (argc == 3)
	{
		s_pid = ft_atoi(argv[1]);
		check_usr_input(argc, s_pid, argv[2][0]);
		signalusr.sa_handler = handle_signal_client;
		signalusr.sa_flags = 0;
		sigemptyset(&signalusr.sa_mask);
		sigaction(SIGUSR1, &signalusr, NULL);
		sigaction(SIGUSR2, &signalusr, NULL);
		ft_printf("sending: \"%s\" to server at pid: %d.\n", argv[2], s_pid);
		send_signal(s_pid, argv[2]);
		return (0);
	}
}
