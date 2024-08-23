#include "../../inc/minishell.h"

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	exit_builtin(char **args)
{
	int			i;
	long int	num;

	i = 0;
	num = 0;
	if (count_args(args) > 2)
		return (printf("bash : %s : too many arguments\n", args[0]), 1);
	if (count_args(args) == 2)
	{
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				printf("bash : %s : %s : numeric argument required\n",
					args[0], args[1]);
				return (1);
			}
			else
				i++;
		}
		num = ft_atoi(args[1]);
		num %= 256;
	}
	exit(num);
}
