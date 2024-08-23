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

void	parsing_error(t_cmdgrp *firstnode, int code, char c)
{
	free_nodes(firstnode);
	if (code == 0)
		printf("minishell: syntax error near unexpected token '%c'\n", c);
	if (code == 1)
		printf("minishell: create or open file near token '%c'\n", c);
}
