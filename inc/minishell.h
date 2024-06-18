/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:03:50 by asaux             #+#    #+#             */
/*   Updated: 2024/06/18 12:00:32 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Library
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
//Struct

typedef struct s_data
{
	char	**env;
}	t_data;

/* Fonctions */

//env.c
void	addshlvl(t_data *data);
int		search_row(t_data *data, char *str);
void	edit_shlvl(t_data *data, int value, int row);
char	**dupenv(char **env);

//utils.c
int		ft_isalldigit(char *str);
void	free_array(char **env);

//bultin/cd.c
void	cd_builtin(char **args, t_data *data);
void	actu_env(char *dir, char *var, t_data *data);
int		go_home(t_data *data, char *old_dir);
int		switch_dir(char *path);
char	*get_home(t_data *data);

//builtin/echo.c
void	echo_builtin(char **args);

//builtin/env.c
void	env_builtin(t_data *data);

//builtin/pwd.c
void	pwd_builtin(void);

//error.c
void	ft_error(char *str);

#endif