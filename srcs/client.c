/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmallet <gmallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:23:34 by gmallet           #+#    #+#             */
/*   Updated: 2023/03/14 08:23:36 by gmallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <time.h>
#include "libft.h"
#include <errno.h>
#include <string.h>

#define KILL_ERROR 1
#define WAIT_ERROR 2

void	print_helper(void)
{
	ft_putstr_fd("use the command as follow:\n", 1);
	ft_putstr_fd("./client <server_pid> <msg>\n", 1);
}

void	log_error(int err)
{
	if (err == KILL_ERROR)
		ft_putstr_fd("error: failed to send signal\n", 1);
	else if (err == WAIT_ERROR)
	{
		ft_putstr_fd("error: failed to wait or server didn't acknowledge\n", 1);
		ft_putstr_fd(strerror(errno), 1);
	}
}

int	send_character(int pid, char c, sigset_t *set, struct timespec *t)
{
	int	i;
	int	ret;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << i))
			ret = kill(pid, SIGUSR2);
		else
			ret = kill(pid, SIGUSR1);
		if (ret)
			return (KILL_ERROR);
		if (sigtimedwait(set, NULL, t) == -1)
			return (WAIT_ERROR);
		++i;
	}
	return (0);
}

int	send_msg(int pid, const char *msg)
{
	int				ret;
	sigset_t		set;
	struct timespec	ts;

	if (pid == 0)
	{
		ft_putstr_fd("invalid pid\n", 1);
		return (1);
	}
	ts.tv_sec = 1;
	ts.tv_nsec = 0;
	sigaddset(&set, SIGUSR1);
	sigprocmask(SIG_BLOCK, &set, NULL);
	while (*msg)
	{
		ret = send_character(pid, *msg, &set, &ts);
		if (ret)
		{
			log_error(ret);
			return (1);
		}
		++msg;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		print_helper();
		return (0);
	}
	return (send_msg(ft_atoi(argv[1]), argv[2]));
}
