
#include "../../inc/minishell.h"

int	mini_countword(char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && !btwn_quote(s, i, 1))
			i++;
		if (s[i])
		{
			count++;
			i += mini_countchar(&s[i], c);
		}
	}
	return (count);
}

/* int	mini_countword(char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && !btwn_quote(s, i, 1))
			i++;
		if (s[i])
		{
			if (is_redir_token(s[i]) && !btwn_quote(s, i, 1) && is_redir_token(s[i + 1]))
					i++;
			count++;
		}
		while ((s[i] != c || btwn_quote(s, i, 1)) && s[i])
		{
			if (is_redir_token(s[i]) && !btwn_quote(s, i, 1))
			{
				if (is_redir_token(s[i + 1]))
					i++;
				count++;
			}
			i++;
		}
	}
	return (count);
} */

char	*mini_strldup(char *s, int len)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc(len + 1);
	if (!res)
		return (res);
	while (i < len && s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	mini_countchar(char *s, char c)
{
	int	i;

	i = 0;
	while ((s[i] != c || btwn_quote(s, i, 1)) && s[i])
	{
		if (is_redir_token(s[i]) && i == 0)
		{
			if (is_redir_token(s[i + 1]))
				return (2);
			return (1);
		}
		else if (is_redir_token(s[i]) && !btwn_quote(s, i, 1))
			return (i);
		else
			i++;
	}
	return (i);
}

char	**mini_split(char *s, char c)
{
	char	**strarray;
	int		i;
	int		j;
	int		k;

	k = mini_countword(s, c);
	strarray = malloc(sizeof(char *) * (k + 1));
	if (!strarray)
		return (NULL);
	i = 0;
	j = 0;
	while (j < k)
	{
		strarray[j] = get_word(s, &i, c);
		j++;
	}
	strarray[j] = 0;
	return (strarray);
}

char	*get_word(char *s, int *i, char c)
{
	char	*new_word;

	while (s[*i] == c && !btwn_quote(s, *i, 1))
		(*i)++;
	if (s[*i])
	{
		new_word = mini_strldup(&s[*i], mini_countchar(&s[*i], c));
		*i += mini_countchar(&s[*i], c);
	}
	return (new_word);
}
