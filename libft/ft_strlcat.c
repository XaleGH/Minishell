/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:31:04 by asaux             #+#    #+#             */
/*   Updated: 2023/10/08 17:53:46 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	char			*sc;

	i = 0;
	j = 0;
	k = 0;
	sc = (char *) src;
	while (dst[i] != '\0' && i < size)
		i++;
	while (sc[j] != '\0')
		j++;
	if (i != size)
	{
		while (sc[k] && i + k < size - 1)
		{
			dst[i + k] = sc[k];
			k++;
		}
		dst[i + k] = '\0';
	}
	return (i + j);
}
