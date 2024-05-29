/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:46:24 by asaux             #+#    #+#             */
/*   Updated: 2023/10/09 15:49:46 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
/*
int	main(void)
{
	printf("%d\n", ft_isalnum('a'));
	printf("%d\n", ft_isalnum('z'));
	printf("%d\n", ft_isalnum('A'));
	printf("%d\n", ft_isalnum('Z'));
	printf("%d\n", ft_isalnum('0'));
	printf("%d\n", ft_isalnum('9'));
	printf("%d\n", ft_isalnum('m'));
	printf("%d\n", ft_isalnum('M'));
	printf("%d\n", ft_isalnum(' '));
	printf("%d\n", ft_isalnum('='));
	printf("%d\n", ft_isalnum('+'));
	printf("%d\n", ft_isalnum(','));
	return (0);
}*/