/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:23:30 by asaux             #+#    #+#             */
/*   Updated: 2023/10/12 16:01:07 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*b;
	unsigned char	*c;

	i = 0;
	b = (unsigned char *) s1;
	c = (unsigned char *) s2;
	while (n-- > 0)
	{
		if (b[i] != c[i])
			return (b[i] - c[i]);
		i++;
	}
	return (0);
}
