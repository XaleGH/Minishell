/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:22:05 by asaux             #+#    #+#             */
/*   Updated: 2023/10/10 14:06:38 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *) s;
	while (n > 0)
	{
		ptr[i] = c;
		i++;
		n--;
	}
	return (s);
}
/*int	main(void)
{
	char s[] = "dkfl";

	printf("%s\n", s);
	printf("%p\n", s);
	ft_memset(s, 'g', 2);
	printf("%s\n", s);
	printf("%p\n", s);
	return (0);
}*/
