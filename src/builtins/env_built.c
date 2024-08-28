/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:55:09 by asaux             #+#    #+#             */
/*   Updated: 2024/08/26 19:54:34 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Executes the internal "env" command.
 *
 * This function prints each environment variable stored in the provided array.
 *
 * @param env_cpy Pointer to an array of strings containing the environment 
 * variables.
 *
 * @return void. The function does not return a value.
 */
void	env_builtin(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strchr(data->env[i], '='))
			printf("%s\n", data->env[i]);
		i++;
	}
	data->exit_status = 0;
}
