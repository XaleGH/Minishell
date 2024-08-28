/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:58:15 by asaux             #+#    #+#             */
/*   Updated: 2024/08/26 19:55:12 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Sorts the environment variables alphabetically.
 *
 * This function sorts the given array of environment variables in 
 * alphabetical order
 * using a simple bubble sort algorithm.
 *
 * @param env Pointer to an array of strings containing the 
 * environment variables.
 *
 * @return char**. Returns a pointer to the sorted array of 
 * environment variables.
 */
char	**sort_env(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], 100) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

void	export_dquote(char **env_cpy, int i)
{
	int		j;
	char	*temp;
	char	*temp2;
	char	*temp3;

	j = 0;
	while (env_cpy[i][j] && env_cpy[i][j] != '=')
		j++;
	if (env_cpy[i][j] != '=')
		return ;
	temp2 = ft_strdup(&env_cpy[i][j + 1]);
	temp = ft_strjoin(temp2, "\"");
	free(temp2);
	env_cpy[i][j + 1] = '\0';
	temp2 = ft_strjoin(env_cpy[i], "\"");
	free(env_cpy[i]);
	env_cpy[i] = temp2;
	temp3 = ft_strjoin(env_cpy[i], temp);
	free(env_cpy[i]);
	free(temp);
	env_cpy[i] = temp3;
}

/*
 * Sorts and prints the environment variables in export format.
 *
 * This function creates a copy of the current environment variables, 
 * sorts them,
 * and prints each variable in the format "declare -x var=value".
 *
 * @param data Pointer to a t_data structure containing the environment
 * variables.
 *
 * @return void. The function does not return a value.
 */
void	sort_and_print_export(t_data *data)
{
	char	**env_cpy;
	int		i;

	i = 0;
	env_cpy = dupenv(data->env);
	env_cpy = sort_env(env_cpy);
	while (env_cpy[i])
	{
		export_dquote(env_cpy, i);
		i++;
	}
	i = 0;
	while (env_cpy[i])
	{
		printf("declare -x %s\n", env_cpy[i]);
		i++;
	}
	free_array(env_cpy);
}

/*
 * Updates an existing environment variable or adds a new one.
 *
 * This function handles the updating or addition of an environment variable in
 * the shell's environment. It performs the following actions:
 *
 * - Calls `add_var_env` to add or update the variable specified by `args[i]`
 * in the current environment (`data->env`).
 * - Frees the memory allocated for the old environment variable array.
 * - Replaces the old environment variable array with the updated one returned
 * by * `add_var_env`.
 *
 * @param args Pointer to an array of strings containing the command's
 * arguments.
 * @param data Pointer to a t_data structure containing the environment
 * variables.
 * @param temp A temporary array to store the new environment variable array.
 * @param i Index of the argument in `args` that represents the environment
 * variable to add or update.
 *
 * @return void. The function does not return a value.
 */
void	export_exist_var(char **args, t_data *data, char **temp, int i)
{
	temp = add_var_env(data->env, args[i]);
	free_array(data->env);
	data->env = temp;
}

/*
 * Replaces an existing environment variable with a new value.
 *
 * This function is responsible for updating an existing environment variable
 * in the shell's environment with a new value provided in `args[i]`.
 * It performs the following actions:
 * - Frees the memory allocated for the existing environment variable at index
 * `j`.
 * - Sets the environment variable at index `j` to `NULL` to ensure no dangling
 * pointer remains.
 * - Allocates memory and duplicates the string from `args[i]` to replace the
 * existing variable.
 *
 * @param args Pointer to an array of strings containing the command's
 * arguments.
 * @param data Pointer to a t_data structure containing the environment
 * variables.
 * @param i Index of the argument in `args` that represents the new value for
 * the environment variable.
 * @param j Index of the environment variable in `data->env` that is being
 * replaced.
 *
 * @return void. The function does not return a value.
 */
void	export_new_var(char **args, t_data *data, int i, int j)
{
	free(data->env[j]);
	data->env[j] = NULL;
	data->env[j] = ft_strdup(args[i]);
}
