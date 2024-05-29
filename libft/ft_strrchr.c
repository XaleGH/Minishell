/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:22:29 by asaux             #+#    #+#             */
/*   Updated: 2023/10/16 10:45:48 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*b;

	b = (char *)s;
	i = ft_strlen(b);
	if ((char) c == '\0')
		return (b + ft_strlen(s));
	while (i >= 0)
	{
		if (b[i] == (char) c)
			return (b + i);
		i--;
	}
	return (NULL);
}
