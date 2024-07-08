#include "../../inc/minishell.h"

void	exit_builtin(char **args, t_data *data)
{
	int			i;
	long int	num;

	i = 0;
	num = 0;
	if (args[2])
	{
		printf("bash : %s : too many arguments\n", args[0]);
		return ;
	}
	if (args[1])
	{
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				printf("bash : %s : %s : numeric argument required\n", args[0], args[1]);
				return ;
			}
			else
				i++;
		}
		num = ft_atoi(args[1]);
		num %= 256;
	}
	exit(num);
}
