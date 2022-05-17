/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:31:45 by fael-bou          #+#    #+#             */
/*   Updated: 2022/05/16 20:07:17 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <sys/_types/_pid_t.h>
#include <sys/signal.h>
#include <unistd.h>

void decode(int signo, siginfo_t *infos, void *ptr)
{
	static int k = 8;
	static char c;
	static pid_t old_pid = -1;

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
		if (c == '\0')
			printf("\nsafi ra salina.. safi ra salaw!");
		k = 8;
		write(1, &c, 1);
		c = 0;
	}
}
// 01 00 11 10
int main ()
{
	struct sigaction act;

	act.sa_sigaction = decode;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);

	printf("%d\n", getpid());
	while(1)
		pause();
}
