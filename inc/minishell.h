/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:03:50 by asaux             #+#    #+#             */
/*   Updated: 2024/07/04 15:39:17 by root             ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

//Struct

typedef struct s_path
{
	char	**cmds;
	char	**allpaths;
	char	*goodpath;
	char	*subpath;
}	t_path;

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

//execute.c
void	execute_ms(char **str, t_data *data);
int		ft_strncmp_exact(char *s1, char *s2, int n);

//utils.c
int		ft_isalldigit(char *str);
void	free_array(char **env);

//bultins/cd.c
void	cd_builtin(char **args, t_data *data);
void	actu_env(char *dir, char *var, t_data *data);
int		go_home(t_data *data, char *old_dir);
int		switch_dir(char *path);
char	*get_home(t_data *data);

//builtins/echo.c
void	echo_builtin(char **args);

//builtins/env.c
void	env_builtin(t_data *data);

//builtins/pwd.c
void	pwd_builtin(void);

//builtins/unset.c
void	unset_builtin(char **args,  t_data *data);

//builtins/export.c
void	export_builtin(char **args, t_data *data);
char	**add_var_env(char **env, char *arg);
char	*recover_arg(char *arg);
int		check_arg(char *arg);

//builtins/export_sort_env.c
char	**sort_env(char **env);
void	sort_and_print_export(t_data *data);

//error.c
void	ft_error(char *str);


#endif