/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:00:51 by asaux             #+#    #+#             */
/*   Updated: 2023/10/12 14:52:06 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	count_set(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (is_set(s1[i], (char *) set) && s1[i])
	{
		j++;
		i++;
	}
	i = ft_strlen(s1);
	if (j != i)
	{
		while (i > 0 && is_set(s1[--i], (char *) set))
			j++;
	}
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int				i;
	unsigned int	k;
	char			*str;

	i = 0;
	if (!set)
		return ((char *) s1);
	if (count_set(s1, set) == ft_strlen(s1) || !s1)
		return (ft_strdup(""));
	str = malloc(sizeof (char) * ((ft_strlen(s1) - count_set(s1, set)) + 1));
	if (!str)
		return (NULL);
	k = 0;
	while (s1[i] && is_set(s1[i], (char *) set))
		i++;
	while (s1[i] && k < (ft_strlen(s1) - count_set(s1, set)))
		str[k++] = s1[i++];
	str[k] = '\0';
	return (str);
}
