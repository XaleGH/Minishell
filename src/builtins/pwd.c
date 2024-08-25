/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:58:49 by asaux             #+#    #+#             */
/*   Updated: 2024/08/25 11:20:55 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Executes the internal "pwd" command.
 *
 * This function prints the current working directory to standard output.
 *
 * @return void. The function does not return a value.
 */
void	pwd_builtin(t_data *data)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	if (!path)
		return (printf("no pwd\n"), exit(1));
	printf("%s\n", path);
	free(path);
	data->exit_status = 0;
}
