/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:58:36 by asaux             #+#    #+#             */
/*   Updated: 2023/10/11 16:55:52 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	k;

	i = 0;
	k = 0;
	if (little[i])
	{
		while (big[i + k] && i + k < len)
		{
			if (big[i + k] == little[k])
				k++;
			else if (little[k] == '\0')
				return ((char *) big + i);
			else
			{
				i++;
				k = 0;
			}
		}
		if (!little[k])
			return ((char *) big + i);
		return (NULL);
	}
	return ((char *) big);
}
