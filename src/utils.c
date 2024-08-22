/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:09:46 by flmuller          #+#    #+#             */
/*   Updated: 2024/08/21 16:53:52 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * check if the given string contain only digit character.
 *
 * @param char. Pointer on the string to be checked.
 *
 * @return int. The function return the row where the given string is find.
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
 * Free the given array .
 *
 * Free the memory allocated of the given array.
 *
 * @param char. pointer to the array.
 *
 * @return void. The function does not return a value.
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

int	ft_strlen_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**rm_from_array(char **array, int i)
{
	int		j;
	int		k;
	int		l;
	char	**newarray;

	j = -1;
	l = 0;
	newarray = ft_calloc(sizeof(char*), ft_strlen_array(array));
	if (!newarray)
		return(NULL);
	while (array[++j])
	{
		if (j != i && array[j])
		{
			k = -1;
			newarray[l] = ft_calloc(sizeof(char), ft_strlen(array[j]) + 1);
			if (!newarray[l])
				return(free_array(newarray), NULL);
			while (array[j][++k])
				newarray[l][k] = array[j][k];
			newarray[l++][k] = '\0';
		}
	}
	free_array(array);
	return (newarray);
}
