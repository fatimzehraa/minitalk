/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:37:02 by fael-bou          #+#    #+#             */
/*   Updated: 2022/05/18 21:12:05 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <sys/_types/_pid_t.h>
#include <sys/signal.h>
#include <unistd.h>

void	ft_putnbr(int n)
{
	char	number;

	if (n >= 0 && n < 10)
	{
		number = n + '0';
		write(1, &number, 1);
	}
	else if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

void	decode(int signo, siginfo_t *infos, void *ptr)
{
	static int		k = 8;
	static char		c;
	static pid_t	old_pid = -1;

	(void)ptr;
	if (infos->si_pid != old_pid)
	{
		k = 8;
		c = 0;
	}
	old_pid = infos->si_pid;
	k--;
	if (signo == SIGUSR2)
		c = c | (1 << k);
	if (k == 0)
	{
		k = 8;
		write(1, &c, 1);
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = decode;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
}
