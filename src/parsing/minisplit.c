
#include "../../inc/minishell.h"

static int	mini_countword(char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && !is_quoted_arg(s, i))
			i++;
		if (s[i])
			count++;
		while ((s[i] != c || is_quoted_arg(s, i)) && s[i])
			i++;
	}
	return (count);
}

static char	*mini_strldup(char *s, int len)
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

static int	mini_countchar(char *s, char c)
{
	int	i;

	i = 0;
	while ((s[i] != c  || is_quoted_arg(s, i)) && s[i])
		i++;
	return (i);
}

char	**mini_split(char *s, char c)
{
	char	**strarray;
	int		i;
	int		j;

	strarray = malloc(sizeof(char *) * (mini_countword(s, c) + 1));
	if (!strarray)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && !is_quoted_arg(s, i))
			i++;
		if (s[i])
		{
			strarray[j] = mini_strldup(&s[i], mini_countchar(&s[i], c));
			j++;
		}
		while ((s[i] != c || is_quoted_arg(s, i)) && s[i])
			i++;
	}
	strarray[j] = 0;
	return (strarray);
}
