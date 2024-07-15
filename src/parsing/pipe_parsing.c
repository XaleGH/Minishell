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

void	parse_on_pipe(t_cmdgrp *node)
{
	int	i;

	i = find_pipe(node->str);
	if (i != -1)
	{
		node->type = PIPE;
		node->part1 = init_cmdgrp(node->str, i);
		node->part2 = init_cmdgrp(&node->str[i + 1],
				ft_strlen(&node->str[i + 1]));
		parse_redexec(node->part1);
		parse_on_pipe(node->part2);
	}
	else
		parse_redexec(node);
}
