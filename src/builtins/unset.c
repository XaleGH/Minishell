#include  "../../inc/minishell.h"

void	unset_builtin(char **args, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		j = search_row(data, args[i]);
		if (j == -1 || data->env[j][ft_strlen(args[i])] != '=')
			printf("unset : %s : Invalid argument\n", args[i]);
		else
		{
			free(data->env[j]);
			while (data->env[j])
			{
				data->env[j] = data->env[j + 1];
				j++;
			}
			free(data->env[j]);
		}
	}
}
