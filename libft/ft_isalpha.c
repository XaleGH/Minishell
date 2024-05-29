/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:24:55 by asaux             #+#    #+#             */
/*   Updated: 2023/10/09 15:54:55 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
/*
int	main(void)
{
	printf("%d\n", ft_isalpha('a'));
	printf("%d\n", ft_isalpha('z'));
	printf("%d\n", ft_isalpha('A'));
	printf("%d\n", ft_isalpha('Z'));
	printf("%d\n", ft_isalpha('0'));
	printf("%d\n", ft_isalpha('9'));
	printf("%d\n", ft_isalpha('m'));
	printf("%d\n", ft_isalpha('M'));
	printf("%d\n", ft_isalpha(' '));
	printf("%d\n", ft_isalpha('='));
	printf("%d\n", ft_isalpha('+'));
	printf("%d\n", ft_isalpha(','));
	return (0);
}*/