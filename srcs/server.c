/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmallet <gmallet@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:18:22 by gmallet           #+#    #+#             */
/*   Updated: 2023/05/02 15:18:48 by gmallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static char			c;
	static unsigned int	i;
	static int			last_client;

	(void)ucontext;
	if (last_client && info->si_pid != last_client)
		i = 0;
	if (sig == SIGUSR2)
		c |= 1 << i;
	i++;
	if (i == 8)
	{
		ft_putchar_fd(c, 1);
		c = 0;
		i = 0;
	}
	kill(info->si_pid, SIGUSR1);
	last_client = info->si_pid;
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
	}
	return (0);
}
