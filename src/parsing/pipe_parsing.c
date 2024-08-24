/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:17:58 by asaux             #+#    #+#             */
/*   Updated: 2024/08/24 14:19:50 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Finds the position of the first unquoted pipe character in a string.
 *
 * This function searches the input string for the first occurrence of the pipe
 * character ('|') that is not enclosed within quotes. It returns the index of 
 * this character if found, or -1 if no such character is found.
 *
 * @param str Pointer to the input string to be searched.
 *
 * @return int. Returns the index of the first unquoted pipe character in 
 * the string. 
 * Returns -1 if no unquoted pipe character is found.
 */
int	find_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && !btwn_quote(str, i, 1))
			return (i);
		i++;
	}
	return (-1);
}

/*
 * Parses a command group based on the presence of pipe characters.
 *
 * This function processes the input command group to handle commands separated
 * by pipe characters ('|').
 * It splits the command string at the first unquoted pipe character and 
 * initializes two new command group nodes for each side of the pipe.
 * It then recursively parses each command group node. If the pipe character is
 * not found, it directly parses the command group for redirections and 
 * executions.
 *
 * @param node Pointer to the current command group node to be parsed.
 * @param firstnode Pointer to the first command group node for error 
 * reporting purposes.
 * @param data Pointer to a data structure containing environment variables 
 * and other relevant information.
 *
 * @return int. Returns 1 if parsing is successful, 0 otherwise.
 */
int	parse_on_pipe(t_cmdgrp *node, t_cmdgrp *firstnode, t_data *data)
{
	int	i;

	i = find_pipe(node->str);
	if (i != -1)
	{
		if (!node->str[i + 1])
			return (parsing_error(firstnode, 0, node->str[i]), 0);
		node->type = PIPE;
		node->part1 = init_cmdgrp(node->str, i);
		node->part2 = init_cmdgrp(&node->str[i + 1],
				ft_strlen(&node->str[i + 1]));
		if (!parse_redexec(node->part1, firstnode, data))
			return (0);
		if (!parse_on_pipe(node->part2, firstnode, data))
			return (0);
	}
	else
	{
		if (!parse_redexec(node, firstnode, data))
			return (0);
	}
	return (1);
}
