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

// inutiliser pour le moment
char	*removechar(char *str, char c)
{
	int		i;
	int		cpt;
	char	*newstr;
	int		j;

	i = 0;
	cpt = 0;
	while (str[i])
		if (str[i++] == c)
			cpt++;
	newstr = malloc(sizeof(char) * (i - cpt + 1));
	if (!newstr)
		return (NULL);
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
	if ((delchar(str, *i, '\'') != 1) && (delchar(str, *i, '"') != 1) && (delchar(str, *i, ' ') != 1))
		(*i)++;
}
