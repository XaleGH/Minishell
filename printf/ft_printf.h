/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:50:57 by asaux             #+#    #+#             */
/*   Updated: 2024/04/29 14:05:53 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *str, ...);
int		check_conv_pf(char c);
void	put_format_pf(int conv, va_list liste, int *count);
void	ft_putchar_pf(char c, int *count);
void	ft_putstr_pf(char *s, int *count);
void	ft_putnbr_pf(int n, int *count);
void	ft_putnbr_ui_pf(unsigned int nbr, char *base, int *count);
void	ft_putnbr_ul_pf(unsigned long nbr, char *base, int *count);
int		ft_strlen_pf(char *s);
void	print_address_pf(va_list liste, int *count);

#endif