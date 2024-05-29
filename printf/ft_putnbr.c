/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:49:17 by asaux             #+#    #+#             */
/*   Updated: 2024/04/29 14:04:21 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_pf(char c, int *count)
{
	*count += write(1, &c, 1);
}

void	ft_putstr_pf(char *s, int *count)
{
	int	i;

	if (!s)
	{
		ft_putstr_pf("(null)", count);
		return ;
	}
	i = 0;
	while (s[i])
	{
		ft_putchar_pf(s[i], count);
		i++;
	}
}

void	ft_putnbr_pf(int n, int *count)
{
	long int	nb;

	nb = n;
	if (n < 0)
	{
		nb = nb * -1;
		ft_putchar_pf('-', count);
	}
	if (nb > 9)
		ft_putnbr_pf((nb / 10), count);
	ft_putchar_pf(((nb % 10) + '0'), count);
}

void	ft_putnbr_ui_pf(unsigned int nbr, char *base, int *count)
{
	unsigned int	lengh;

	lengh = ft_strlen_pf(base);
	if (nbr >= lengh)
	{
		ft_putnbr_ui_pf(nbr / lengh, base, count);
		ft_putchar_pf(base[(nbr % lengh)], count);
	}
	else if (nbr < lengh)
		ft_putchar_pf(base[nbr], count);
}

void	ft_putnbr_ul_pf(unsigned long nbr, char *base, int *count)
{
	unsigned long	lengh;

	lengh = ft_strlen_pf(base);
	if (nbr >= lengh)
	{
		ft_putnbr_ul_pf(nbr / lengh, base, count);
		ft_putchar_pf(base[(nbr % lengh)], count);
	}
	else if (nbr < lengh)
		ft_putchar_pf(base[nbr], count);
}
