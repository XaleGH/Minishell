
#include "../../inc/minishell.h"

void	parse_redexec(t_cmdgrp *node)
{
	int	i;

	node->arg = mini_split(node->str, ' ');
	i = 0;
	while (node->arg[i])
	{
		printf("%s\n",node->arg[i]);
		i++;
	}
	//printf("test\n");
	i = 0;
	while (node->arg[i])
	{
		if (node->arg[i][0] == '>' && node->arg[i][1] && node->arg[i][1] != '>')
			;//error //unepexted token node->arg[i][1]
		else if (node->arg[i][0] == '<' && node->arg[i][1] && node->arg[i][1] != '<')
			;//error //unepexted token node->arg[i][1]
		else if (node->arg[i][0] == '>' || node->arg[i][0] == '<')
			parse_redir(node, i);
		else
		{
			node->arg[i] = clean_arg(node->arg[i]);
			i++;
		}
		if (node->type == DEFAULT)
			node->type = EXEC;
	}
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

void	init_parsing(char *line)
{
	t_cmdgrp	*node;
	t_cmdgrp	*firstnode;

	node = init_cmdgrp(line, ft_strlen(line));
	firstnode = node;
	parse_on_pipe(node);
	print_node(firstnode);
}
//$? retour derniere fonction code retour
//$env