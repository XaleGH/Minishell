/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:44:23 by asaux             #+#    #+#             */
/*   Updated: 2023/10/09 16:31:12 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
/*
int	main(void)
{
	printf("%d\n", ft_isdigit('a'));
	printf("%d\n", ft_isdigit('z'));
	printf("%d\n", ft_isdigit('A'));
	printf("%d\n", ft_isdigit('Z'));
	printf("%d\n", ft_isdigit('0'));
	printf("%d\n", ft_isdigit('9'));
	printf("%d\n", ft_isdigit(120));
	printf("%d\n", ft_isdigit(130));
	printf("%d\n", ft_isdigit(' '));
	printf("%d\n", ft_isdigit('='));
	printf("%d\n", ft_isdigit('+'));
	printf("%d\n", ft_isdigit(','));
	return (0);
}*/