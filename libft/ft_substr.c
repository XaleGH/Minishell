/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:02:12 by asaux             #+#    #+#             */
/*   Updated: 2023/10/12 13:04:44 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen((char *) s))
		return (ft_strdup(""));
	if (len > ft_strlen((char *) s + start))
		sub = malloc (sizeof (char) * (ft_strlen((char *) s + start) + 1));
	else
		sub = malloc (sizeof (char) * (len + 1));
	if (!sub)
		return (NULL);
	while (s[start] && i < len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
