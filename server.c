/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:36:56 by npederen          #+#    #+#             */
/*   Updated: 2025/02/03 17:36:56 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*g_message = NULL;

char	*ft_strjoinchar(char *s1, char carac)
{
	char	*str;
	size_t	i;

	i = 0;
	str = ft_calloc((ft_strlen(s1) + 2), sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = carac;
	str[i + 1] = 0;
	free(s1);
	return (str);
}

void	handle_signal(int signum, siginfo_t *info, void *data)
{
	static char	octet = 0;
	static int	i = 0;

	(void)data;
	if (!g_message)
		g_message = ft_strdup("");
	if (signum == SIGUSR1)
		octet |= (0 << (7 - i));
	else if (signum == SIGUSR2)
		octet |= (1 << (7 - i));
	i++;
	if (i == 8)
	{
		g_message = ft_strjoinchar(g_message, octet);
		if (!octet)
		{
			ft_putstr_fd(g_message, 1);
			free(g_message);
			g_message = NULL;
			kill(info->si_pid, SIGUSR1);
		}
		octet = 0;
		i = 0;
	}
	kill(info->si_pid, SIGUSR2);
}

//sigemptyset is there to mask an invalid valgrind error 🦈
int	main(int argc, char **argv)
{
	struct sigaction	signalusr;

	(void) argv;
	if (argc == 1)
	{
		signalusr.sa_sigaction = handle_signal;
		signalusr.sa_flags = SA_SIGINFO;
		sigemptyset(&signalusr.sa_mask);
		sigaction(SIGUSR1, &signalusr, NULL);
		sigaction(SIGUSR2, &signalusr, NULL);
		ft_printf("Le PID de mon server est: %i\n", getpid());
		while (1)
			pause();
		free(g_message);
	}
	exit(1);
	return (0);
}
