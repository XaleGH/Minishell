
#include "../../inc/minishell.h"

int	find_pipe(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && !is_quoted_arg(str, i))
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
		node->str[i] = '\0';
		node->part1 = init_cmdgrp(node->str);
		node->part2 = init_cmdgrp(&node->str[i + 1]);
		parse_redexec(node->part1);
		parse_on_pipe(node->part2);
	}
	parse_redexec(node);
}

void	parse_redexec(t_cmdgrp *node)
{
	int i;
	if (find_redir(node->str) != -1)
	{
		printf("test\n");
		i = 1;
		i++;
		//parse_redir(node);
	}
	else
	{
		parse_exec(node);
	}
}

void	parse_exec(t_cmdgrp *node)
{
	int	i;

	node->type = EXEC;
	node->arg = mini_split(node->str, ' ');
	i = -1;
	while (node->arg[++i])
		node->arg[i] = clean_arg(node->arg[i]);
}

//verifier le cas ou on supprime le dernier caractere
char	*clean_arg(char *str)
{
	int		i;
	int		j;
	char *dupstr;

	dupstr = strdup(str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (btwn_quote(dupstr, j++) == 1)
		{
			printf("in quote\n");
			if (delchar(&str, i, '\'') != 1)
				i++;
		}
		else if (btwn_quote(dupstr, j++) == 2)
		{
			printf("in double quote\n");
			if (delchar(&str, i, '"') != 1)
				i++;
		}
		else
		{
			j++;
			printf("not in quote\n");
			if ((delchar(&str, i, '\'') != 1) && (delchar(&str, i, '"') != 1) && (delchar(&str, i, ' ') != 1))
				i++;
		}
		printf("%c\n", str[i]);
		printf("%c\n", dupstr[j]);
	}
	free (dupstr);
	return (str);
}

int	delchar(char **str, int pos, char c)
{
	char	*newstr;
	int		i;
	int		j;

	if (str[0][pos] == c)
	{
		newstr = malloc(sizeof(char) * (ft_strlen(str[0])));
		i = 0;
		j = 0;
		while (str[0][i])
		{
			if (i != pos)
				newstr[j++] = str[0][i];
			i++;
		}
		newstr[j] = '\0';
		free(str[0]);
		str[0] = newstr;
		return (1);
	}
	return (0);
}

// inutiliser pour le moment
char	*removechar(char *str, char c)
{
	int		i;
	int		cpt;
	char	*newstr;
	int		j;

	i = 0;
	cpt = 0;
	while(str[i])
		if (str[i++] == c)
			cpt++;
	newstr = malloc(sizeof(char) * (i - cpt + 1));
	if (!newstr)
		return NULL;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
			newstr[j++] = str[i];
		i++;
	}
	newstr[j] = '\0'; 
	free(str);
	return (newstr);
}

/* void	parse_redir(t_cmdgrp *node)
{

} */

int	find_redir(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '<' || str[i] == '>') &&  !is_quoted_arg(str, i))
			return (i);
		i++;
	}
	return (-1);
}

t_cmdgrp	*init_cmdgrp(char *line)
{
	t_cmdgrp	*new_node;

	new_node = malloc(sizeof(t_cmdgrp));
	if (!new_node)
		return (NULL);
	new_node->type = DEFAULT;
	new_node->str = line;
	return (new_node);
}

void	init_parsing(char *line)
{
	t_cmdgrp	*node;

	node = init_cmdgrp(line);
	parse_on_pipe(node);
	print_node(node);
}
