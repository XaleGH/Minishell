/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:13:27 by asaux             #+#    #+#             */
/*   Updated: 2023/10/16 10:45:56 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*b;

	i = 0;
	b = (char *) s;
	if (!c)
		return (b + ft_strlen(s));
	while (b[i])
	{
		if (b[i] == (char) c)
			return (b + i);
		i++;
	}
	if (b[i] == (char) c)
		return (b + i);
	return (NULL);
}

/*int	main(void)
{
	char str[] = "Hello world";
	char *recup;

	recup = ft_strchr(str, 'w');
	printf("%s", recup);
	return (0);
}*/