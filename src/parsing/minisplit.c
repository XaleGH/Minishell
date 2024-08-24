/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:06:15 by asaux             #+#    #+#             */
/*   Updated: 2024/08/24 14:12:16 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Counts the number of words in a string, separated by a specified delimiter.
 *
 * This function iterates through the given string and counts the number of 
 * words, where words are sequences of characters separated by the specified 
 * delimiter `c`.
 * It also considers whether characters are within quotes and skips delimiters 
 * inside quotes.
 *
 * @param s Pointer to the string in which to count the words.
 * @param c The character used as a delimiter to separate words.
 *
 * @return int. The function returns the number of words found in the string.
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
 * Duplicates a substring from the beginning of a given string up to a 
 * specified length.
 *
 * This function allocates memory and copies the first `len` characters 
 * from the input string `s` into the newly allocated memory. If the length 
 * specified is greater than the length of the string, it copies up to the 
 * end of the string. The resulting string is null-terminated.
 *
 * @param s Pointer to the source string to duplicate from.
 * @param len The number of characters to copy from the source string.
 *
 * @return char*. Returns a pointer to the newly allocated string containing 
 * the duplicated substring.
 * Returns NULL if memory allocation fails.
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
 * Counts the number of characters in a string until a specified delimiter 
 * is encountered.
 *
 * This function iterates through the given string, counting characters until 
 * it finds the delimiter `c`, considering whether the delimiter is within 
 * quotes. It also checks for specific redirection tokens at the beginning of 
 * the string and adjusts the count accordingly.
 *
 * @param s Pointer to the string in which to count characters.
 * @param c The character used as the delimiter to stop counting.
 *
 * @return int. Returns the number of characters counted until the delimiter is
 * found or the end of the string.
 * Returns 2 if a redirection token is found and followed by another 
 * redirection token at the beginning, and 1 if a redirection token is found 
 * alone at the beginning.
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
 * Splits a string into an array of substrings based on a specified delimiter.
 *
 * This function divides the input string `s` into substrings separated by the 
 * delimiter `c`. 
 * It allocates memory for an array of string pointers and fills it with 
 * substrings extracted from the input string. The array is null-terminated 
 * to indicate the end of the array.
 *
 * @param s Pointer to the input string to be split.
 * @param c The delimiter character used to split the string.
 *
 * @return char**. Returns a pointer to an array of strings (substrings). 
 * Returns NULL if memory allocation fails.
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
 * Extracts a substring from a given string based on a specified delimiter.
 *
 * This function extracts a word from the input string `s`, starting at the 
 * index pointed to by `i` and continuing until the delimiter character `c` 
 * is encountered. It skips over any delimiters and handles cases where the 
 * delimiter might be within quotes. 
 * The extracted substring is allocated dynamically and returned.
 *
 * @param s Pointer to the input string from which to extract the substring.
 * @param i Pointer to the current index in the string from which to start 
 * extracting.
 * @param c The delimiter character that marks the end of the substring.
 *
 * @return char*. Returns a pointer to the newly allocated substring. 
 * Returns NULL if there are no characters to extract or if memory allocation 
 * fails.
 */
char	*get_word(char *s, int *i, char c)
{
	char	*new_word;

	new_word = NULL;
	while (s[*i] == c && !btwn_quote(s, *i, 1))
		(*i)++;
	if (s[*i])
	{
		new_word = mini_strldup(&s[*i], mini_countchar(&s[*i], c));
		*i += mini_countchar(&s[*i], c);
	}
	return (new_word);
}
