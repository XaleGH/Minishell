/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:12:33 by asaux             #+#    #+#             */
/*   Updated: 2024/08/24 14:17:24 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Parses and processes command arguments for redirection and execution.
 *
 * This function takes a command group node and processes its arguments to 
 * handle input/output redirections and prepare them for execution. It splits 
 * the command string into individual arguments, replaces environment variables,
 * and checks for redirection operators. It validates the syntax of redirections
 * and cleans the arguments for further processing.
 *
 * @param node Pointer to the command group node containing the command string 
 * to be parsed.
 * @param firstnode Pointer to the first node of the command group, used for 
 * error reporting.
 * @param data Pointer to a data structure containing environment variables and 
 * other relevant information.
 *
 * @return int. Returns 1 if parsing and processing were successful, 0 if an 
 * error occurred during redirection parsing or syntax checking.
 */
int	parse_redexec(t_cmdgrp *node, t_cmdgrp *firstnode, t_data *data)
{
	int	i;

	node->arg = mini_split(node->str, ' ');
	node->arg = env_replace(node->arg, data);
	i = 0;
	while (node->arg[i])
	{
		if ((node->arg[i][0] == '>' || node->arg[i][0] == '<'))
		{
			if (check_syn_redir(node, i) != 0)
				return (parsing_error(firstnode, 0,
						check_syn_redir(node, i)), 0);
			if (!parse_redir(node, i, firstnode))
				return (0);
		}
		else
		{
			node->arg[i] = clean_arg(node->arg[i]);
			i++;
		}
		if (node->type == DEFAULT)
			node->type = EXEC;
	}
	return (1);
}

/*
 * Initializes a new command group node with the specified command line.
 *
 * This function allocates memory for a new `t_cmdgrp` structure, initializes 
 * its fields with default values, and copies a specified portion of the input 
 * command line into the `str` field of the new node.
 * The `type` is set to `DEFAULT`, and other fields are set to NULL or default 
 * values.
 *
 * @param line Pointer to the input command line string to be copied into the 
 * node.
 * @param len The length of the portion of the command line to be copied.
 *
 * @return t_cmdgrp*. Returns a pointer to the newly allocated `t_cmdgrp` 
 * structure.
 * Returns NULL if memory allocation fails.
 */
t_cmdgrp	*init_cmdgrp(char *line, int len)
{
	t_cmdgrp	*new_node;

	new_node = malloc(sizeof(t_cmdgrp));
	if (!new_node)
		return (NULL);
	new_node->type = DEFAULT;
	new_node->part1 = NULL;
	new_node->part2 = NULL;
	new_node->arg = NULL;
	new_node->str = mini_strldup(line, len);
	return (new_node);
}

/*
 * Initializes and parses a command line into a command group structure.
 *
 * This function creates a new command group node from the input command line 
 * and initializes it. It then processes the node to handle commands separated 
 * by pipes. If parsing fails, it returns NULL. Otherwise, it returns a pointer
 * to the first node of the command group.
 *
 * @param line Pointer to the input command line string to be parsed.
 * @param data Pointer to a data structure containing environment variables and
 * other relevant information.
 *
 * @return t_cmdgrp*. Returns a pointer to the first node of the command group 
 * if parsing is successful.
 * Returns NULL if parsing fails or memory allocation fails.
 */
t_cmdgrp	*init_parsing(char *line, t_data *data)
{
	t_cmdgrp	*node;
	t_cmdgrp	*firstnode;

	node = init_cmdgrp(line, ft_strlen(line));
	firstnode = node;
	if (!parse_on_pipe(node, firstnode, data))
		return (NULL);
	return (firstnode);
}
