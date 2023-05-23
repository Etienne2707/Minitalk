#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int	ft_atoi(char *str2)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str2[i] >= 9 && str2[i] <= 13) || str2[i] == 32)
		i++;
	if (str2[i] == '+')
		i++;
	else if (str2[i] == '-')
	{
		i++;
		sign = sign * -1;
	}
	while (str2[i] >= '0' && str2[i] <= '9' && str2[i] != '\0')
	{
		result *= 10;
		result = result + str2[i] - '0';
		i++;
	}
	return (result * sign);
}

void	ft_send_bits(int pid, char i)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((i & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int pid;
	int i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid < 0)
			return (0);
		while (argv[2][i] != '\0')
		{
			ft_send_bits(pid, argv[2][i]);
			i++;
		}
		ft_send_bits(pid, '\n');
	}
	else
	{
		printf("\033[91mError: wrong format.\033[0m\n");
		printf("\033[33mTry: ./client <PID> <MESSAGE>\033[0m\n");
		return (1);
	}
	return (0);
}