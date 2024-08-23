#include "../../inc/minishell.h"

char	**env_replace(char **arg, t_data *data)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		arg[i] = replace_env_in_arg(arg[i], data);
		i++;
	}
	return (arg);
}

char	*replace_env_in_arg(char *arg, t_data *data)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!btwn_quote(arg, i, 0) || btwn_quote(arg, i, 0) == 2)
		{
			if (arg[i] == '$' && ft_isdigit(arg[i + 1]))
				i += replace_nothing(&arg, i);
			else if (arg[i] == '$' && arg[i + 1] == '?')
				i += replace_lexit(&arg, i, data);
			else if (arg[i] == '$' && arg[i + 1])
				i += replace_var(&arg, i, data);
			else
				i++;
		}
		else
			i++;
	}
	return (arg);
}

int	replace_nothing(char **arg, int i)
{
	(*arg)[i] = '\0';
	*arg = ft_strjoin(*arg, &(*arg)[i + 2]);
	return (0);
}

int	replace_lexit(char **arg, int i, t_data *data)
{
	(*arg)[i] = '\0';
	*arg = ft_strjoin(ft_strjoin(*arg, ft_itoa(data->exit_status)),
			&(*arg)[i + 2]);
	return (ft_strlen(ft_itoa(data->exit_status)));
}

int	replace_var(char **arg, int i, t_data *data)
{
	char	*temp;
	char	*envvar;
	int		j;
	int		k;

	(*arg)[i] = '\0';
	k = 0;
	j = i + 1;
	while ((*arg)[j] && (*arg)[j] != '$' && (*arg)[j++] != ' ')
		;
	temp = malloc(sizeof(char) * ((j - i)));
	while (++i <= j)
		temp[k++] = (*arg)[i];
	if (search_row(data, temp) == -1)
		return ((*arg = ft_strjoin(*arg, &(*arg)[j])), free(temp), 0);
	envvar = data->env[search_row(data, temp)];
	free(temp);
	k = 0;
	while (envvar[k] != '=')
		k++;
	temp = ft_strdup(&envvar[k + 1]);
	*arg = ft_strjoin(ft_strjoin(*arg, temp), &(*arg)[j]);
	return (free(temp), j - i);
}
