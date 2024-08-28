/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:58:57 by asaux             #+#    #+#             */
/*   Updated: 2024/08/28 10:39:53 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Executes the internal "unset" command.
 *
 * This function removes the specified environment variables from the shell's
 * environment.
 * For each argument provided, it searches for the corresponding environment
 * variable and,if found, removes it by shifting subsequent variables in the 
 * array.
 * If the argument is invalid or not found, it prints an error message.
 *
 * @param args Pointer to an array of strings containing the variable names 
 * to unset.
 * @param data Pointer to a structure containing the environment data.
 *
 * @return void. The function does not return a value.
 */
void	unset_builtin(char **args, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		j = search_row(data, args[i]);
		if (j == -1)
			ft_printf("unset : %s : Invalid argument\n", args[i]);
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
	data->exit_status = 0;
}
