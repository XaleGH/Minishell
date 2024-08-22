#include "../inc/minishell.h"

/*
 * Handles errors by printing an error message and exiting the program.
 *
 * This function sets the errno to 1, prints the provided error message along with the error description,
 * and then exits the program with a status code of 1.
 *
 * @param str Pointer to a string containing the error message to be printed.
 *
 * @return void. The function does not return a value.
 */
void	ft_error(char *str)
{
	errno = 1;
	perror(str);
	exit(1);
}

void	free_nodes(t_cmdgrp *node)
{
	if (node->type == 1)
	{
		free_nodes(node->part1);
		free_nodes(node->part2);
	}
	free_node_content(node);
	free(node);
}

void	free_node_content(t_cmdgrp *node)
{
	if (node->str != NULL)
		free(node->str);
	if (node->arg != NULL)
		free_array(node->arg);
}
