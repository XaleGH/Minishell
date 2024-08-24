/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:37:56 by asaux             #+#    #+#             */
/*   Updated: 2024/08/24 14:42:30 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * Increments the value of the SHLVL environment variable.
 *
 * This function locates the "SHLVL" variable in the environment, increments
 * its value by 1, and updates the environment with the new value. If the
 * "SHLVL" variable does not exist or its value is not a valid number, it sets
 * the value to 2.
 *
 * @param data Pointer to the t_data structure containing environment variables.
 * 
 * @return This function does not return a value. It modifies the environment
 * variables directly by calling edit_shlvl() with the updated SHLVL value.
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
 * Searches for the index of an environment variable in the environment array.
 *
 * This function looks for the environment variable whose name matches the
 * specified string (str). It returns the index of the environment variable if
 * found; otherwise, it returns -1 if the variable is not present in the
 * environment.
 * The function considers a variable name to match if it starts with the
 * specified string and is followed by either '=' or the end of the string.
 *
 * @param data Pointer to the t_data structure containing the environment
 * variables.
 * @param str  The name of the environment variable to search for.
 *
 * @return The index of the environment variable in the `data->env` array if
 * found; otherwise, -1.
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
 * Updates the SHLVL environment variable in the environment array.
 *
 * This function modifies the SHLVL environment variable by updating its value
 * to the specified level. The value is converted to a string and the
 * environment variable is updated accordingly. The function assumes that the
 * SHLVL variable already exists in the environment array and will replace its
 * current value with the new one.
 *
 * @param data Pointer to the t_data structure containing the environment
 * variables.
 * @param value The new value to be set for the SHLVL variable.
 * @param row The index of the SHLVL variable in the `data->env` array.
 */
void	edit_shlvl(t_data *data, int value, int row)
{
	int		len_num;
	char	*str_num;
	char	*str;

	str_num = ft_itoa(value);
	len_num = ft_strlen(str_num);
	str = malloc(sizeof(char) * (6 + 1 + len_num));
	str = "SHLVL=";
	if (!str)
		return ;
	str = ft_strjoin(str, str_num);
	free(data->env[row]);
	data->env[row] = NULL;
	data->env[row] = str;
	free(str_num);
}

/*
 * Duplicates an array of environment variables.
 *
 * This function creates a new array of environment variables by duplicating
 * each string from the original array. The new array is allocated with the same
 * number of elements as the original array plus one for the NULL terminator.
 *
 * @param env The original array of environment variable strings.
 * @return A new array of environment variable strings that is a duplicate of
 * the input array. The new array is dynamically allocated and should be freed
 * by the caller when no longer needed.
 */
char	**dupenv(char **env)
{
	int		i;
	char	**dup_env;

	i = 0;
	while (env[i])
		i++;
	dup_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		dup_env[i] = ft_strdup(env[i]);
		i++;
	}
	dup_env[i] = NULL;
	return (dup_env);
}
