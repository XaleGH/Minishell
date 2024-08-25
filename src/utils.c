/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:14:01 by asaux             #+#    #+#             */
/*   Updated: 2024/08/25 11:39:24 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * Checks if all characters in the string are digits.
 *
 * This function verifies that every character in the given string is a digit
 * (0-9).
 * It returns 1 (true) if all characters are digits, and 0 (false) otherwise.
 *
 * @param str The string to check.
 * @return 1 if all characters in the string are digits; otherwise, returns 0.
 */
int	ft_isalldigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
 * Frees an array of strings.
 *
 * This function iterates through an array of strings, freeing each individual
 * string and then freeing the array itself. It ensures that all allocated
 * memory for the array and its elements is properly released.
 *
 * @param array A pointer to an array of strings to be freed. The array itself
 * and all its elements are deallocated.
 */
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

/*
 * Calculates the number of strings in an array of strings.
 *
 * This function counts the number of non-null elements in a null-terminated
 * array of strings. It iterates through the array until it encounters a null
 * pointer, which signifies the end of the array.
 *
 * @param array A pointer to an array of strings. The array is assumed to be
 * null-terminated.
 *
 * @return The number of strings in the array, excluding the null terminator.
 */
int	ft_strlen_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/*
 * Removes an element from a null-terminated array of strings.
 *
 * This function creates a new array of strings that is identical to the input
 * array, except that the element at index `i` is excluded. Memory for the new
 * array and its elements is dynamically allocated. If memory allocation fails,
 * the function returns `NULL`. The original array is freed.
 *
 * @param array The input array of strings from which an element will be
 * removed.
 * This array is expected to be null-terminated.
 * @param i The index of the element to be removed from the array. The index is
 * zero-based.
 *
 * @return A new array of strings with the specified element removed, or `NULL`
 * if memory allocation fails. The new array is also null-terminated.
 */
char	**rm_from_array(char **array, int i)
{
	int		j;
	int		k;
	int		l;
	char	**newarray;

	j = -1;
	l = 0;
	newarray = ft_calloc(sizeof(char *), ft_strlen_array(array));
	if (!newarray)
		return (NULL);
	while (array[++j])
	{
		if (j != i && array[j])
		{
			k = -1;
			newarray[l] = ft_calloc(sizeof(char), ft_strlen(array[j]) + 1);
			if (!newarray[l])
				return (free_array(newarray), NULL);
			while (array[j][++k])
				newarray[l][k] = array[j][k];
			newarray[l++][k] = '\0';
		}
	}
	free_array(array);
	return (newarray);
}

/*
 * Skips leading whitespace characters in a string.
 *
 * This function identifies and skips over any leading whitespace characters
 * in the provided string. Whitespace characters include spaces (' ') and 
 * other common whitespace characters like tabs, newlines, and carriage returns.
 *
 * - The function iterates through the string until it encounters a character
 * that is not a whitespace character.
 * - Whitespace characters are considered as ' ' (space), '\t' (horizontal tab),
 * '\n' (newline), '\v' (vertical tab), '\f' (form feed), and '\r'
 * (carriage return).
 *
 * @param str Pointer to the string from which leading whitespace will be
 * skipped.
 *
 * @return The index of the first non-whitespace character in the string.
 */
int	ignore_w_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}
