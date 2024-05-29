/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:30:25 by asaux             #+#    #+#             */
/*   Updated: 2023/10/11 16:22:33 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*b;
	unsigned char	*c;

	i = 0;
	b = (unsigned char *) s1;
	c = (unsigned char *) s2;
	while ((b[i] && i < n) || (c[i] && i < n))
	{
		if (b[i] != c[i])
			return (b[i] - c[i]);
		if (b[i] == '\0' && c[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}
