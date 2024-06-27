#include "../inc/minishell.h"

// fichier de test a supprimer

void	print_node(t_cmdgrp *node)
{
	int	i;

	i = 0;
	printf("<<<<<<<<<NEW NODE>>>>>>>>>\ntype : %d\nstr : %s\n", node->type, node->str);
	if (node->type == 0)
	{
		while (node->arg[i])
		{
			printf("arg %d : @%s@\n", i, node->arg[i]);
			i++;
		}
	}
	else if (node->type ==1)
	{
		print_node(node->part1);
		print_node(node->part2);
	}
}