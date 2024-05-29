/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:13:36 by asaux             #+#    #+#             */
/*   Updated: 2023/10/16 10:41:00 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	char			*b;

	i = 0;
	b = (char *) s;
	while (i < n)
	{
		if (b[i] == (char) c)
			return (b + i);
		i++;
	}
	return (NULL);
}
