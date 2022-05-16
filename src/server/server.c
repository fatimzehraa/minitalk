/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:37:02 by fael-bou          #+#    #+#             */
/*   Updated: 2022/05/14 22:13:56 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <signal.h>
#include <sys/signal.h>
#include <unistd.h>

void sig_handler(int signo)
{
	if (signo == SIGUSR1)
		write(1, "0", 1);
	else if (signo == SIGUSR2)
		write(1, "1", 1);
}

void decode(int signo)
{
	static int k = 8;
	static char c;

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
// 01 00 11 10
int main ()
{
	printf("%d\n", getpid());
	signal (SIGUSR1, decode);
	signal(SIGUSR2, decode);
	printf("world\n");
	while(1);
}
