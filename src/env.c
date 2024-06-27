
#include "../inc/minishell.h"

/*
 * Increment the current env shlvl.
 *
 * @param t_data Pointer data struct with an enviromenent tab initialize.
 *
 * @return void. The function does not return a value.
 */
void	addshlvl(t_data *data)
{
	int		row;
	int		i;
	int		value;

	i = 0;
	row = search_row(data, "SHLVL\0");
	value = 2;
	if (row > -1)
	{
		while (data->env[row][i]
			&& (data->env[row][i] < '0' || data->env[row][i] > '9'))
			i++;
		if (ft_isalldigit(&data->env[row][i]))
			value = ft_atoi(&data->env[row][i]) + 1;
	}
	edit_shlvl(data, value, row);
}

/*
 * search the first row where the given string appear.
 *
 * this function search the first appearance of given string in the environement
 * tab of the data struct.
 *
 * @param t_data pointer to the s_data struct initialize.
 * @param str Pointer to a string containing the string to be search 
 * in the environement.
 *
 * @return int. The function return the row where the given string is find.
 * return -1 if there is no given string present in environement.
 */
int	search_row(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(str, data->env[i], ft_strlen(str)) == 0
			&& (data->env[i][ft_strlen(str) == '='
			|| data->env[i][ft_strlen(str)] == '\0']))
			return (i);
		i++;
	}
	return (-1);
}

/*
 * replace shlvl row with the new row.
 *
 * replace the shlvl row in the current env with the new value given.
 *
 * @param t_data. pointer to the s_data struct initialize.
 * @param int. value of the new shlvl.
 * @param int. row of the shlvl line in the current environement.
 *
 * @return int. The function return the row where the given string is find.
 * @return void. The function does not return a value.
 */
void	edit_shlvl(t_data *data, int value, int row)
{
	int		len_num;
	char	*str_num;
	char	*str;

	str_num = ft_itoa(value);
	len_num = ft_strlen(str_num);
	str = malloc(sizeof(char) * (6 + 1 + len_num));
	if (!str)
		return ;
	str = ft_strjoin("SHLVL=", str_num);
	free(data->env[row]);
	data->env[row] = NULL;
	data->env[row] = str;
	free(str_num);
}

/*
 * Duplicate the given env.
 *
 * Duplicate the given environement to a new environement tab.
 *
 * @param char. pointer on environement tab to be duplicate.
 * 
 * @return char. The function return new environement tab.
 */
char	**dupenv(char **env)
{
	int		i;
	char	**dup_env;

	i = 0;
	while (env[i])
		i++;
	dup_env = malloc(sizeof(char**) * (i + 1));
	i = 0;
	while (env[i])
	{
		dup_env[i] = ft_strdup(env[i]);
		i++;
	}
	dup_env[i] = NULL;
	return (dup_env);
}
