/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 09:44:27 by amezoe            #+#    #+#             */
/*   Updated: 2024/12/26 17:40:48 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"


static void	sig_action(int sig, siginfo_t *info, void *context)
{
	static int				i = 0;
	static pid_t			client_pid = 0;
	static unsigned char	bruh = 0;

	(void) context;
	if (!client_pid)
		client_pid = info->si_pid;
	bruh |= (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!bruh)
		{
			kill (client_pid, SIGUSR2);
			client_pid = 0;
			return ;
		}
		ft_putchar_fd(bruh, 1);
		bruh = 0;
		kill (client_pid, SIGUSR1);
	}
	else
		bruh <<= 1;
}

int	main (void)
{
	struct sigaction	s_sigaction;
	
	ft_putstr_fd("Server PID is ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	s_sigaction.sa_sigaction = sig_action;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}
