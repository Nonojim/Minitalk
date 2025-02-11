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

//struct sigaction {
//	void     (*sa_handler)(int);
//	void     (*sa_sigaction)(int, siginfo_t *, void *);
//	sigset_t   sa_mask;
//	int        sa_flags;
//	void     (*sa_restorer)(void);
//};           

//int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

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

void handle_signal(int signum)
{
	static char	*message;
	static char	octet;
	static int	i = 0;
	if(!message)
		message = ft_strdup("");
	if (signum == SIGUSR1)
		octet |= (0 << (7 - i));
	else if (signum == SIGUSR2)
		octet |= (1 << (7 - i));
	i++;
	if(i == 8)
	{
		message = ft_strjoinchar(message, octet);
		if (!octet)
		{
			//ft_printf("%s\n", message);
			ft_putstr_fd(message, 1);
			free(message);
			message = NULL;
		}
		octet = 0;
		i = 0;
	}
}
int	main(void)
{
	struct	sigaction signalusr;

	signalusr.sa_handler = handle_signal;
	signalusr.sa_flags = 0;
	sigemptyset(&signalusr.sa_mask); //ne bloque rien mais cache erreur valgrind
	sigaction(SIGUSR1, &signalusr, NULL);
	sigaction(SIGUSR2, &signalusr, NULL);
	ft_printf("Le PID de mon server est: %i\n", getpid());
	while(1)
		pause();
	return(0);
}