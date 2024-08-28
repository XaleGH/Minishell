/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:58:12 by asaux             #+#    #+#             */
/*   Updated: 2024/08/27 15:34:54 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	put_format(int conv, va_list liste, int *count)
{
	if (conv == 'c')
		ft_putchar_pf(va_arg(liste, int), count);
	else if (conv == 's')
		ft_putstr_pf(va_arg(liste, char *), count);
	else if (conv == 'p')
		print_address(liste, count);
	else if (conv == 'd' || conv == 'i')
		ft_putnbr_pf(va_arg(liste, int), count);
	else if (conv == 'u')
		ft_putnbr_ui_pf(va_arg(liste, unsigned int), "0123456789", count);
	else if (conv == 'x')
		ft_putnbr_ui_pf(va_arg(liste, unsigned int), "0123456789abcdef", count);
	else if (conv == 'X')
		ft_putnbr_ui_pf(va_arg(liste, unsigned int), "0123456789ABCDEF", count);
	else if (conv == '%')
		ft_putchar_pf(conv, count);
}

void	print_address(va_list liste, int *count)
{
	unsigned long	pvalue;

	pvalue = va_arg(liste, unsigned long);
	if (!pvalue)
		ft_putstr_pf("(nil)", count);
	else
	{
		ft_putstr_pf("0x", count);
		ft_putnbr_ul_pf(pvalue, "0123456789abcdef", count);
	}
}

int	check_conv(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%');
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	liste;

	i = 0;
	count = 0;
	va_start(liste, format);
	while (format[i])
	{
		if (format[i] != '%')
			ft_putchar_pf(format[i], &count);
		else
		{
			i++;
			if (check_conv(format[i]))
				put_format(format[i], liste, &count);
		}
		i++;
	}
	va_end(liste);
	return (count);
}
