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

//void sendsignal(int PID; char* message)
//{
//	
//}

void	send_signal(int PID, char* str)
{
	int	i;
	int	j;
	unsigned char bit;

	j = 0;
	bit = 0;
	while(str[j])
	{
		i = 8;
		while (i-- > 0)
		{
			bit = ((str[j] >> i) & 1);
			if(bit == 0)
				kill(PID, SIGUSR1);
			else if(bit == 1)
				kill(PID, SIGUSR2);
			usleep(100);
			write(1, &bit, 1);
		}
			j++;
	}
	i = 8;
	while (i-- > 0)
	{
		kill(PID, SIGUSR1);
		usleep(100);
	}
}
int	main(int argc, char *argv[])
{
	int PID;
	if (argc != 3)
	{
		ft_printf("3 necessary arguments, follow example: ./client <PID> <message>\n");
		return(0);
	}
	PID = ft_atoi(argv[1]);
	if (!PID)
	{
		ft_printf("invalid PID \n");
		return(0);
	}
	if (argv[2][0] == 0)
	{
		ft_printf("Empty message, no signal sent\n");
		return(0);
	}
	ft_printf("sending: \"%s\" to server at PID: %d.\n", argv[2], PID);
	send_signal(PID, argv[2]);
	write(1, "\n", 1);
	return(0);
}