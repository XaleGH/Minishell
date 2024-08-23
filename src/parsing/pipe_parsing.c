#include "../../inc/minishell.h"

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
