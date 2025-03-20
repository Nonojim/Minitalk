/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:04:20 by npederen          #+#    #+#             */
/*   Updated: 2025/03/20 01:04:20 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	check_usr_input(int narg, int s_pid, char c)
{
	if (narg != 3)
	{
		ft_printf("Error !, follow example: ./client <s_pid> <message>\n");
		exit(1);
	}
	if (!s_pid || kill(s_pid, 0) == -1)
	{
		ft_printf("invalid pid \n");
		exit(1);
	}
	if (c == 0)
	{
		ft_printf("Empty message, no signal sent\n");
		exit(1);
	}
	return (1);
}
