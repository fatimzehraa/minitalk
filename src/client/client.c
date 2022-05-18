/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:36:45 by fael-bou          #+#    #+#             */
/*   Updated: 2022/05/18 16:29:51 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <sys/_types/_pid_t.h>
#include <sys/signal.h>
#include <unistd.h>
#include <errno.h>

int	ft_atoi(char *str, int *pid)
{
	int	i;

	i = 0;
	*pid = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		*pid = *pid * 10 + str[i] - '0';
		i++;
	}
	return (1);
}

void	encode(char a, pid_t pid)
{
	char	i;
	int		out;

	i = 8;
	while (i--)
	{
		out = a & (1 << i);
		if (out == 0)
		{
			kill (pid, SIGUSR1);
		}
		else if (out > 0)
		{
			kill(pid, SIGUSR2);
		}
		usleep(500);
	}
}

int	minitalk(char *str, char *s_pid)
{
	int	i;
	int	pid;

	if (ft_atoi(s_pid, &pid) == 1 && kill(pid, 0) == 0 && pid)
	{
		i = 0;
		while (str[i])
		{
			encode (str[i], pid);
			i++;
		}
		encode('\0', pid);
		return (1);
	}
	else
	{
		write(1, "invalid pid\n", 12);
		return (0);
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
		return (1);
	if (minitalk(argv[2], argv[1]))
		return (0);
	return (1);
}
