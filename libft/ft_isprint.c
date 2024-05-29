/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:55:18 by asaux             #+#    #+#             */
/*   Updated: 2023/10/09 16:34:55 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c < 127);
}
/*
int	main(void)
{
	printf("%d\n", ft_isprint('a'));
	printf("%d\n", ft_isprint('z'));
	printf("%d\n", ft_isprint('A'));
	printf("%d\n", ft_isprint('Z'));
	printf("%d\n", ft_isprint('0'));
	printf("%d\n", ft_isprint('9'));
	printf("%d\n", ft_isprint(28));
	printf("%d\n", ft_isprint(130));
	printf("%d\n", ft_isprint(' '));
	printf("%d\n", ft_isprint('='));
	printf("%d\n", ft_isprint('+'));
	printf("%d\n", ft_isprint(','));
	return (0);
}*/