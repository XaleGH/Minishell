/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmuller <flmuller@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:03:50 by asaux             #+#    #+#             */
/*   Updated: 2024/06/17 17:01:58 by flmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Library
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

//Struct

typedef struct s_data
{
	char	**env;
}	t_data;

/* Fonctions */

/* env.c */

void	addshlvl(t_data *data);
int		search_row(t_data *data, char *str);
void	edit_shlvl(t_data *data, int value, int row);
char	**dupenv(char **env);

/* utils.c */

int		ft_isalldigit(char *str);
void	free_array(char **env);

#endif