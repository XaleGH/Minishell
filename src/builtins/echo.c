/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:52:43 by asaux             #+#    #+#             */
/*   Updated: 2024/08/24 23:16:57 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Executes the internal "echo" command.
 *
 * This function prints the provided arguments to the standard output.
 * It handles the "-n" option, which suppresses the trailing newline character.
 * If no arguments are provided, it simply prints a newline.
 *
 * @param args Pointer to an array of strings 
 * containing the command's arguments.
 *
 * @return void. The function does not return a value.
 */
void	echo_builtin(char **args)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (args[i])
	{
		while (args[i] && (ft_strncmp_exact(args[i], "-n", 2) == 0))
		{
			i++;
			flag = 1;
		}
		while (args[i])
		{
			printf("%s", args[i]);
			i++;
			if (args[i])
				printf(" ");
		}
	}
	if (flag == 0)
		printf("\n");
}
