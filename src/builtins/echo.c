/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:52:43 by asaux             #+#    #+#             */
/*   Updated: 2024/08/25 11:20:05 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Checks if the provided string is a valid "-n" option for the echo command.
 *
 * This function determines whether the given string corresponds to the `-n`
 * option used in the `echo` command, which suppresses the trailing newline.
 * It performs the following checks:
 *
 * - If the string does not start with a dash ('-'), it returns 1, indicating
 * that the string is not a valid option.
 * - If the string starts with a dash, the function checks if all following
 * characters are 'n'.
 * - If the string consists only of "-n" with one or more 'n' characters,
 * the function returns 0, indicating that the string is a valid option.
 * - If any character after the initial dash is not 'n', it returns 1,
 * indicating that the string is not a valid option.
 *
 * @param str Pointer to the string to be checked for the "-n" option.
 *
 * @return 0 if the string is a valid "-n" option, otherwise 1.
 */
int	echo_option(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (1);
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

/*
 * Executes the internal "echo" command.
 *
 * This function prints the provided arguments to the standard output.
 * It handles the "-n" option, which suppresses the trailing newline character.
 * If no arguments are provided, it simply prints a newline.
 *
 * @param args Pointer to an array of strings 
 * containing the command's arguments.
 * @param data Pointer to a t_data structure containing the environment
 * variables.
 *
 * @return void. The function does not return a value.
 */
void	echo_builtin(char **args, t_data *data)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (args[i])
	{
		while (args[i] && (echo_option(args[i]) == 0))
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
	data->exit_status = 0;
}
