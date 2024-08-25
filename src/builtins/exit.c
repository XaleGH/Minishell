/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:55:32 by asaux             #+#    #+#             */
/*   Updated: 2024/08/25 20:05:03 by asaux            ###   ########.fr       */
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
 * Validates and processes the argument for the "exit" command.
 *
 * This function checks if the argument provided to the "exit" command is a
 * valid numeric value. It performs the following actions:
 * - Iterates through the characters of the argument string to verify that it
 * contains only digits (with an optional leading '-' for negative numbers).
 * - If a non-digit character is found, it prints an error message indicating
 * that a numeric argument is required and returns `1` to signal an error.
 * - If the argument is valid, it converts the string to a long integer using
 * `ft_atoi`.
 * The result is stored in the variable pointed to by `num`.
 * - The value of `num` is then reduced modulo 256, as exit status codes
 * typically range from 0 to 255.
 * - The function also prints "exit" to signal the termination of the shell.
 *
 * @param args Pointer to an array of strings containing the command's arguments
 * @param num Pointer to a long integer where the numeric value of the argument
 * will be stored.
 *
 * @return 0 if the argument is valid and processed successfully; 1 if an error
 * occurs.
 */
int	exit_utils(char **args, long int *num)
{
	int	i;

	i = 0;
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
	*num = ft_atoi(args[1]);
	*num %= 256;
	printf("exit\n");
	return (0);
}

/*
 * Handles the "exit" command, terminating the shell.
 *
 * This function processes the "exit" command, validating its arguments and
 * determining the appropriate exit status. It performs the following actions:
 *
 * - If more than one argument is provided, it prints an error message
 * indicating that too many arguments were given and returns `1` to signal an
 * error.
 * - If exactly one argument is provided, it calls `exit_utils` to validate the
 * argument and convert it to a numeric value stored in `num`.
 * - It checks the shell level (`SHLVL`) in the environment. If the shell level
 * is 2, the function frees the environment array to clean up before exiting.
 * - The function then sets `data->exit_status` to the calculated exit status
 * `num`, frees the nodes saved in `data->save_node`, and calls `exit` to
 * terminate the shell with the specified exit status.
 *
 * @param args Pointer to an array of strings containing the command's arguments
 * @param data Pointer to a t_data structure containing environment variables
 * and other shell-related data.
 *
 * @return 1 if the function reaches the end, although it typically does not
 * return as it calls `exit` to terminate the shell.
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
		exit_utils(args, &num);
	i = search_row(data, "SHLVL=");
	if (data->env[i][6] == '2' && data->env[i][7] == '\0')
		free_array(data->env);
	return ((data->exit_status = num), free_nodes(data->save_node),
		exit(num), 1);
}
