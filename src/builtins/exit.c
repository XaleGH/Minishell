/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:55:32 by asaux             #+#    #+#             */
/*   Updated: 2024/08/25 17:26:58 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Counts the number of arguments in an array of strings.
 *
 * This function iterates through the provided array of arguments and counts
 * how many non-null strings are present.
 *
 * @param args Pointer to an array of strings containing the arguments.
 *
 * @return int. Returns the number of arguments in the array.
 */
int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

/*
 * Executes the internal "exit" command.
 *
 * This function handles the termination of the shell process. It checks the 
 * arguments provided to the "exit" command to ensure they are valid. If a 
 * numeric argument is provided, it exits with the corresponding status code.
 * If more than one argument is provided, or if the argument is not numeric, 
 * it prints an error message.
 *
 * @param args Pointer to an array of strings containing the command's arguments.
 * @param data Pointer to a t_data structure containing the environment
 * variables.
 * 
 * @return int. Returns 1 in case of an error (too many arguments or non-numeric
 * argument), otherwise, the function does not return as it exits the program.
 */
int	exit_builtin(char **args, t_data *data)
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
			if (args[1][i] == '-')
				i++;
			if (!ft_isdigit(args[1][i]))
				return (printf("bash : %s : %s : numeric argument required\n",
						args[0], args[1]), 1);
			else
				i++;
		}
		num = ft_atoi(args[1]);
		num %= 256;
	}
	printf("exit\n");
	i = search_row(data, "SHLVL=");
	if (data->env[i][6] == '2' && data->env[i][7] == '\0')
		free_array(data->env);
	return ((data->exit_status = num), free_nodes(data->save_node), exit(num), 1);
}
