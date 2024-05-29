/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:51:51 by asaux             #+#    #+#             */
/*   Updated: 2023/10/09 16:28:10 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
/*
int	main(void)
{
	printf("%d\n", ft_isascii('a'));
	printf("%d\n", ft_isascii('z'));
	printf("%d\n", ft_isascii('A'));
	printf("%d\n", ft_isascii('Z'));
	printf("%d\n", ft_isascii('0'));
	printf("%d\n", ft_isascii('9'));
	printf("%d\n", ft_isascii(120));
	printf("%d\n", ft_isascii(130));
	printf("%d\n", ft_isascii(' '));
	printf("%d\n", ft_isascii('='));
	printf("%d\n", ft_isascii('+'));
	printf("%d\n", ft_isascii(','));
	return (0);
}*/