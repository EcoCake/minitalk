/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 09:44:22 by amezoe            #+#    #+#             */
/*   Updated: 2024/12/26 17:33:30 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

static void	sig_action(int sig)
{
	static int received;

	received = 0;
	if (sig == SIGUSR1)
		received++;
	else
	{
		ft_putnbr_fd(received, 1);
		ft_putchar_fd('\n', 1);
		exit (0);
	}
}

static void send_bits(int PID, char *str)
{
	int		i;
	char	store;

	while (*str)
	{
		store = *str++;
		i = 7;
		while (i >= 0)
		{
			if (store >> i & 1)
				kill (PID, SIGUSR2);
			else
				kill (PID, SIGUSR1);
			usleep(100);
			i--;
		}
	}
	i = 7;
	while (i >= 0)
	{
		kill(PID, SIGUSR1);
		usleep(100);
		i--;
	}
}

int main (int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
		return (1);
	ft_putstr_fd("Sent     :  ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Received:  ", 1);
	signal(SIGUSR1, sig_action);
	signal(SIGUSR2, sig_action);
	send_bits(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
