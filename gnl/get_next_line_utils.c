/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:10:08 by asaux             #+#    #+#             */
/*   Updated: 2023/11/09 11:01:28 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr_gnl(char *s, int c)
{
	int		i;

	i = -1;
	if (!s)
		return (0);
	if (!c)
		return (0);
	while (s[++i])
		if (s[i] == c)
			return (1);
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		len;

	len = ft_strlen_gnl(s2);
	if (!s1)
		return (ft_strndup_gnl(s2, len));
	len = len + ft_strlen_gnl(s1);
	str = malloc(sizeof (char) * (len + 1));
	if (!str)
		return (free(s1), (char *) NULL);
	i = 0;
	len = 0;
	while (s1[i])
		str[len++] = s1[i++];
	i = 0;
	while (s2[i])
		str[len++] = s2[i++];
	str[len] = 0;
	free(s1);
	return (str);
}

char	*ft_strndup_gnl(char *s1, int l)
{
	char	*str;
	int		i;

	i = -1;
	if (!s1 || !l)
		return (NULL);
	str = malloc(sizeof(char) * (l + 1));
	if (!str)
		return (NULL);
	while (++i < l)
		str[i] = s1[i];
	str[i] = 0;
	return (str);
}
