/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:18:59 by asaux             #+#    #+#             */
/*   Updated: 2023/10/09 13:55:08 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_unit(long int save, int unit, int n)
{
	while (save > 9)
	{
		save = save / 10;
		unit++;
	}
	unit++;
	if (n < 0)
		unit++;
	return (unit);
}

char	*ft_itoa(int n)
{
	long int	save;
	int			unit;
	char		*tab;

	save = n;
	unit = 0;
	if (n < 0)
		save = save * -1;
	unit = count_unit(save, unit, n);
	tab = malloc(sizeof (char) * unit + 1);
	if (!tab)
		return (NULL);
	tab[unit--] = '\0';
	while (save > 9)
	{
		tab[unit--] = (save % 10) + '0';
		save = save / 10;
	}
	tab[unit] = save + '0';
	if (n < 0)
		tab[--unit] = '-';
	return (tab);
}
/*
int	main(void)
{
	char *f = ft_itoa(-2147483648);
	char *s = ft_itoa(2147483647);
	char *d = ft_itoa(0);
	printf("%s : %s : %s\n", f, s ,d);
	return (0);
}*/