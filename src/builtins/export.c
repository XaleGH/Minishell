/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:58:34 by asaux             #+#    #+#             */
/*   Updated: 2024/08/27 16:00:48 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Checks if an argument is a valid environment variable assignment.
 *
 * This function verifies if the provided argument contains an '=' character,
 * indicating a valid environment variable assignment. If the argument is 
 * invalid,
 * it prints an error message.
 *
 * @param arg Pointer to a string containing the argument to check.
 *
 * @return int. Returns 0 if the argument is valid, or 1 if the argument is 
 * invalid.
 */
int	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		i++;
	}
	ft_printf("export : %s : Invalid argument\n", arg);
	return (1);
}

/*
 * Extracts the variable name from an environment variable assignment.
 *
 * This function takes a string in the format "var=value" and extracts the 
 * variable name "var".
 *
 * @param arg Pointer to a string containing the environment variable 
 * assignment.
 *
 * @return char*. Returns a pointer to a newly allocated string containing 
 * the variable name.
 */
char	*recover_arg(char *arg)
{
	int		i;
	int		j;
	char	*reco_arg;

	i = 0;
	while (arg[i] != '=')
		i++;
	reco_arg = malloc(sizeof(char) * (i + 1));
	j = 0;
	while (j < i)
	{
		reco_arg[j] = arg[j];
		j++;
	}
	reco_arg[j] = '\0';
	return (reco_arg);
}

/*
 * Adds a new environment variable to the environment array.
 *
 * This function creates a new environment array that includes the original 
 * environment variables
 * plus the new variable specified by the arg parameter.
 *
 * @param env Pointer to an array of strings containing the current 
 * environment variables.
 * @param arg Pointer to a string containing the new environment variable 
 * to add.
 *
 * @return char**. Returns a pointer to the new environment array with 
 * the added variable.
 */
char	**add_var_env(char **env, char *arg)
{
	int		i;
	char	**dup_env;

	i = 0;
	while (env[i])
		i++;
	dup_env = malloc(sizeof(char **) * (i + 2));
	i = 0;
	while (env[i])
	{
		dup_env[i] = ft_strdup(env[i]);
		i++;
	}
	dup_env[i] = ft_strdup(arg);
	dup_env[i + 1] = NULL;
	return (dup_env);
}

/*
 * Executes the internal "export" command.
 *
 * This function adds or updates environment variables based on 
 * the provided arguments.
 * If no arguments are given, it sorts and prints the current 
 * environment variables.
 *
 * @param args Pointer to an array of strings containing the 
 * command's arguments.
 * @param data Pointer to a t_data structure containing the 
 * environment variables.
 *
 * @return void. The function does not return a value.
 */
void	export_builtin(char **args, t_data *data)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	temp = NULL;
	if (!args[1])
		return (sort_and_print_export(data));
	while (args[++i])
	{
		j = search_row(data, args[i]);
		if (j == -1)
			export_exist_var(args, data, temp, i);
		else
			export_new_var(args, data, i, j);
	}
	data->exit_status = 0;
}
