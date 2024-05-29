/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:41:57 by asaux             #+#    #+#             */
/*   Updated: 2023/10/11 16:22:39 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*#include <string.h>
int	main(void)
{
	char s[] = "dkfl";
	char f[] = "dkfl";

	printf("%s\n", s);
	printf("%p\n", s);
	ft_bzero(s, 2);
	printf("%s\n", s);
	printf("%p\n", s);
	printf("%s\n", f);
	printf("%p\n", f);
	bzero(s, 2);
	printf("%s\n", f);
	printf("%p\n", f);
	return (0);
}*/