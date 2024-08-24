/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:26:42 by asaux             #+#    #+#             */
/*   Updated: 2024/08/24 15:27:10 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fichier de test a supprimer

void	print_node(t_cmdgrp *node)
{
	int	i;

	i = 0;
	printf("<<<<<<<<<NEW NODE>>>>>>>>>\ntype : %d\nstr : %s\nfd : %d\n",
		node->type, node->str, node->fd);
	if (node->type == 0 || node->type == 2 || node->type == 3)
	{
		while (node->arg[i])
		{
			printf("arg %d : @%s@\n", i, node->arg[i]);
			i++;
		}
	}
	else if (node->type == 1)
	{
		print_node(node->part1);
		print_node(node->part2);
	}
}
