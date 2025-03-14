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

//void sendsignal(int s_pid; char* message)
//{
//	
//}

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
			usleep(4000);
			write(1, &bit, 1);
		}
		j++;
	}
	i = 8;
	while (i-- > 0)
	{
		kill(s_pid, SIGUSR1);
		usleep(4000);
	}
}

void	handle_signal(int signum)
{
	ft_printf("The server got your message.\n");
	if (signum == SIGINT)
		exit(0);
	else
		ft_putstr_fd("The signal is not supported.", 1);
}

int	main(int argc, char *argv[])
{
	struct sigaction	signalusr;
	int					s_pid;

	if (argc != 3)
	{
		ft_printf("error !, follow example: ./client <s_pid> <message>\n");
		return (0);
	}
	s_pid = ft_atoi(argv[1]);
	if (!s_pid)
	{
		ft_printf("invalid pid \n");
		return (0);
	}
	if (argv[2][0] == 0)
	{
		ft_printf("Empty message, no signal sent\n");
		return (0);
	}
	signalusr.sa_handler = handle_signal;
	signalusr.sa_flags = 0;
	sigaction(SIGINT, &signalusr, NULL);
	ft_printf("sending: \"%s\" to server at pid: %d.\n", argv[2], s_pid);
	send_signal(s_pid, argv[2]);
	write(1, "\n", 1);
	return (0);
}
