/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:00:17 by asaux             #+#    #+#             */
/*   Updated: 2024/08/24 14:06:01 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Replaces environment variables in the provided arguments.
 *
 * This function iterates through an array of argument strings and replaces any
 * environment variable placeholders with their corresponding values from the 
 * shell'senvironment.
 *
 * @param arg Pointer to an array of strings containing the arguments to 
 * process.
 * @param data Pointer to a structure containing the environment data.
 *
 * @return char**. Returns a pointer to the modified array of argument strings.
 */
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

/*
 * Replaces environment variables within a single argument string.
 *
 * This function processes a given argument string and replaces any environment
 * variable placeholders (e.g., $VAR) with their corresponding values from the 
 * shell's environment. It handles special cases such as `$?` for the last exit
 * status and numeric variables. Quoted sections within the string are treated 
 * appropriately.
 *
 * @param arg Pointer to a string containing the argument to process.
 * @param data Pointer to a structure containing the environment data.
 *
 * @return char*. Returns a pointer to the modified argument string.
 */
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

/*
 * Removes a numeric environment variable placeholder from an argument string.
 *
 * This function handles the case where a `$` is followed by a digit, which 
 * typically represents a positional parameter or an invalid environment 
 * variable. It effectively removes the `$` and the digit from the argument 
 * string.
 *
 * @param arg Pointer to a pointer to the argument string to modify.
 * @param i The index in the string where the `$` character is located.
 *
 * @return int. Returns 0, indicating that no additional characters need 
 * to be skipped.
 */
int	replace_nothing(char **arg, int i)
{
	(*arg)[i] = '\0';
	*arg = ft_strjoin(*arg, &(*arg)[i + 2]);
	return (0);
}

/*
 * Replaces the `$?` placeholder in an argument string with the last exit 
 status.
 *
 * This function handles the special case where `$?` appears in the argument 
 * string, replacing it with the value of the last command's exit status. 
 * The function updates the argument string accordingly and returns the length 
 * of the inserted exit status.
 *
 * @param arg Pointer to a pointer to the argument string to modify.
 * @param i The index in the string where the `$?` placeholder is located.
 * @param data Pointer to a structure containing the environment data, 
 * including the exit status.
 *
 * @return int. Returns the length of the inserted exit status string.
 */
int	replace_lexit(char **arg, int i, t_data *data)
{
	(*arg)[i] = '\0';
	*arg = ft_strjoin(ft_strjoin(*arg, ft_itoa(data->exit_status)),
			&(*arg)[i + 2]);
	return (ft_strlen(ft_itoa(data->exit_status)));
}

/*
 * Replaces an environment variable placeholder in an argument string
 * with its value.
 *
 * This function identifies and replaces an environment variable placeholder 
 * (e.g., `$VAR`) in the argument string with its corresponding value from the 
 * shell's environment. 
 * If the environment variable is not found, the placeholder is simply removed 
 * from the string.
 *
 * @param arg Pointer to a pointer to the argument string to modify.
 * @param i The index in the string where the `$` character is located.
 * @param data Pointer to a structure containing the environment data.
 *
 * @return int. Returns the number of characters processed, allowing for 
 * proper indexing in the caller function.
 */
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
