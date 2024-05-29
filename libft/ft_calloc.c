/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:58:25 by asaux             #+#    #+#             */
/*   Updated: 2023/10/23 15:56:34 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*str;

	if (!nmemb || !size)
		return (malloc(0));
	if ((nmemb * size) > 2147483647)
		return (0);
	str = malloc(nmemb * size);
	if (!str)
		return (NULL);
	ft_bzero(str, (nmemb * size));
	return (str);
}

/*int	main(void)
{
	char *str;

	str = calloc(6, 1);
	free(str);
	return(0);
}*/