/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:37:56 by asaux             #+#    #+#             */
/*   Updated: 2024/08/26 15:57:52 by asaux            ###   ########.fr       */
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
 * Updates the "SHLVL" environment variable to the specified value.
 *
 * This function modifies the "SHLVL" (Shell Level) environment variable to
 * reflect the current shell level. It performs the following actions:
 * - Converts the integer `value` into a string using `ft_itoa`.
 * - Allocates memory for a new string that will hold the updated "SHLVL" value,
 * which is a combination of the prefix "SHLVL=" and the string representation
 * of `value`.
 * - Copies the prefix "SHLVL=" into the newly allocated string and concatenates
 * the string representation of `value` to form the complete "SHLVL" entry.
 * - Frees the previous "SHLVL" value in `data->env[row]` and replaces it with
 * the newly constructed string.
 * - Frees any temporary memory used during the process.
 *
 * @param data Pointer to a t_data structure containing the environment
 * variables.
 * @param value The new shell level value to set for "SHLVL".
 * @param row The index in the environment variable array where "SHLVL"
 * is stored.
 *
 * @return void. The function does not return a value.
 */
void	edit_shlvl(t_data *data, int value, int row)
{
	int		len_num;
	char	*str_num;
	char	*str;
	char	*prefix;

	prefix = "SHLVL=";
	str_num = ft_itoa(value);
	len_num = ft_strlen(str_num);
	str = malloc(sizeof(char) * (ft_strlen(prefix) + len_num + 1));
	if (!str)
	{
		free(str_num);
		return ;
	}
	ft_strlcpy(str, prefix, ft_strlen(prefix) + 1);
	ft_strlcat(str, str_num, ft_strlen(prefix) + len_num + 1);
	free(str_num);
	free(data->env[row]);
	data->env[row] = ft_strdup(str);
	free(str);
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

/*
 * Determines the position where an environment variable name ends in a string.
 *
 * This function iterates through the string `arg`, starting from index `j`, to
 * find the position where the current environment variable name terminates.
 * The end of the variable name is identified by the presence of a special
 * character that indicates the boundary of the variable name or the beginning
 * of another token.
 *
 * The iteration stops at any of the following characters:
 * - `$` (indicating the start of another environment variable)
 * - `'` or `"` (indicating the beginning of a quoted string)
 * - A space character (indicating the end of the token)
 *
 * @param j The starting index for the search in the string `arg`.
 * @param arg The string containing the environment variable name.
 *
 * @return int The index marking the end of the environment variable name.
 */
int	check_env_end(int j, char *arg)
{
	while (arg[j] && arg[j] != '$' && arg[j] != '\''
		&& arg[j] != '\"' && arg[j] != ' ')
		j++;
	return (j);
}
