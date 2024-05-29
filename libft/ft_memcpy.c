/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:45:08 by asaux             #+#    #+#             */
/*   Updated: 2023/10/09 10:52:45 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int	i;

	i = 0;
	if (!src && !dest)
		return (0);
	while (i < (int) n)
	{
		((char *) dest)[i] = ((char *) src)[i];
		i++;
	}
	return (dest);
}
