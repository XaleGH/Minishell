#include "../inc/minishell.h"

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
