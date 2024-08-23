#include "../../inc/minishell.h"

/*
 * check if given chars match any of separator.
 *
 * @param char	char to test.
 * 
 * @return int	1 if it s match separator test 0 if not.
 */
int	is_separator(char c)
{
	return (c == ' ' || c == '|' || c == '<' || c == '>');
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

//verifier le cas ou on supprime le dernier caractere
char	*clean_arg(char *str)
{
	int		i;
	int		j;
	char	*dupstr;

	dupstr = strdup(str);
	i = 0;
	j = 0;
	while (dupstr[j])
	{
		if (btwn_quote(dupstr, j, 0) == 1)
		{
			if (delchar(&str, i, '\'') != 1)
				i++;
		}
		else if (btwn_quote(dupstr, j, 0) == 2)
		{
			if (delchar(&str, i, '"') != 1)
				i++;
		}
		else
			apply_all_clean(&str, &i);
		j++;
	}
	free(dupstr);
	return (str);
}

void	apply_all_clean(char **str, int *i)
{
	if ((delchar(str, *i, '\'') != 1) && (delchar(str, *i, '"') != 1)
		&& (delchar(str, *i, ' ') != 1))
		(*i)++;
}

char	check_syn_redir(t_cmdgrp *node, int i)
{
	if (node->arg[i][0] == '>' || node->arg[i][0] == '<')
	{
		if (node->arg[i][0] == '>' && node->arg[i][1] && node->arg[i][1] != '>')
			return (node->arg[i][1]);
		else if (node->arg[i][0] == '<'
			&& node->arg[i][1] && node->arg[i][1] != '<')
			return (node->arg[i][1]);
		else if ((node->arg[i][0] == '>' || node->arg[i][0] == '<')
			&& !node->arg[i + 1])
		{
			if ((node->arg[i][0] == '>' && !node->arg[i][1]))
				return (0);
			else
				return (node->arg[i][0]);
		}
		else if (node->arg[i + 1] && is_separator(node->arg[i + 1][0]))
			return (node->arg[i + 1][0]);
		else
			return (0);
	}
	else
		return (0);
}
