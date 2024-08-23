#include "../../inc/minishell.h"

/*
 * count word in the given string
 *
 * this split count parameter .
 *
 * @param char*	pointer to first character of string.
 * @param char	delimiter.
 *
 * @return int number of parameter of the given string
 */
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

/*
 * duplicate string
 *
 * duplicate string for x char where x = len.
 *
 * @param char*	pointer to first character of string.
 * @param int lenght of character to be duplicate.
 *
 * @return char* pointer on the first character of the duplicate string.
 */
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

/*
 * count char in the given string before delimiter
 *
 * @param char*	pointer to first character of string.
 * @param char	delimiter.
 *
 * @return int number of character in the string before delimiter
 */
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

/*
 * create an array of string where each string is a parameter
 *
 * @param char*	pointer to first character of string.
 * @param char	delimiter.
 *
 * @return char ** pointer on the array of parameter
 */
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

/*
 * return a dup of the next word
 *
 * @param char*	pointer to first character of string.
 * @param int*	currentposition in the string.
 * @param char	delimiter.
 *
 * @return char* return a dup of the next word.
 */
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
