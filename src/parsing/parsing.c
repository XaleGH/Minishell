#include "../../inc/minishell.h"

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

void	init_parsing(char *line, t_data *data)
{
	t_cmdgrp	*node;
	t_cmdgrp	*firstnode;

	node = init_cmdgrp(line, ft_strlen(line));
	firstnode = node;
	if (parse_on_pipe(node, firstnode, data))
		print_node(firstnode);
}
