

#include <stdio.h>
#include <signal.h>
#include <sys/_types/_pid_t.h>
#include <sys/signal.h>

static int	is_space(char a)
{
	if (a == '\t' || a == '\n' || a == '\v'
		|| a == '\f' || a == '\r' || a == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	k;

	i = 0;
	n = 0;
	k = 1;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k = k * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	return (n * k);
}

void encode(char a, pid_t pid)
{
	char i;
	int k;
	int out;
	char bin[8];

	i = 8;
	k = 0;
	while (i--)
	{
		out = a & (1<<i);
		if (out == 0)
		{
			kill (pid, SIGUSR1);
			bin[k] = '0';
//			printf("0");
			}
		else if (out > 0)
		{
			kill(pid, SIGUSR2);
			bin[k] = '1';
//			printf("1");
		}
		usleep(500);
		k++;
	}
//	printf("%s\n", bin);
}

int main (int argc, char *argv[])
{
//	char *pid;

//	pid = argv[1];
//	kill(pid, SIGUSR1)
	int i;
	i = 0;
//	char *array = argv[1];
	while(argv[2][i])
	{
		encode (argv[2][i], ft_atoi(argv[1]));
		i++;
	}
	printf("hello\n");

}
