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
	return (str);
}

void	send_confirmation(int cpid)
{
	kill(cpid, SIGINT);
}

void	handle_signal(int signum, siginfo_t *info, void *data)
{
	static char	*message;
	static char	octet;
	static int	i = 0;

	(void)data;
	if (!message)
		message = ft_strdup("");
	if (signum == SIGUSR1)
		octet |= (0 << (7 - i));
	else if (signum == SIGUSR2)
		octet |= (1 << (7 - i));
	i++;
	if (i == 8)
	{
		message = ft_strjoinchar(message, octet);
		if (!octet)
		{
			ft_putstr_fd(message, 1);
			free(message);
			message = NULL;
			send_confirmation(info->si_pid);
		}
		octet = 0;
		i = 0;
	}
}

//sigemptyset is there to mask an invalid valgrind error
int	main(void)
{
	struct sigaction	signalusr;

	signalusr.sa_sigaction = handle_signal;
	signalusr.sa_flags = SA_SIGINFO;
	sigemptyset(&signalusr.sa_mask);
	sigaction(SIGUSR1, &signalusr, NULL);
	sigaction(SIGUSR2, &signalusr, NULL);
	ft_printf("Le PID de mon server est: %i\n", getpid());
	while (1)
		pause();
	return (0);
}
