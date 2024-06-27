
#ifndef MINISHELL_H
# define MINISHELL_H

//Library
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
//Struct

typedef struct s_data
{
	char	**env;
}	t_data;

typedef enum s_tokentype
{
	EXEC,
	PIPE,
	REDIR,
	IN_REDIR,
	OUT_REDIR,
	HEREDOC,
	APPEND,
	DEFAULT
}	t_tokentype;

typedef struct s_cmdgrp
{
	int			type;
	int			subtype;
	struct s_cmdgrp	*part1;
	struct s_cmdgrp	*part2;
	char		*str;
	char		**arg;
}	t_cmdgrp;
/* Fonctions */

//env.c
void		addshlvl(t_data *data);
int			search_row(t_data *data, char *str);
void		edit_shlvl(t_data *data, int value, int row);
char		**dupenv(char **env);

//utils.c
int			ft_isalldigit(char *str);
void		free_array(char **env);
int			btwn_quote(char *str, int poschar);
int			is_quoted_arg(char *str, int poschar);

//bultin/cd.c
void		cd_builtin(char **args, t_data *data);
void		actu_env(char *dir, char *var, t_data *data);
int			go_home(t_data *data, char *old_dir);
int			switch_dir(char *path);
char		*get_home(t_data *data);

//builtin/echo.c
void		echo_builtin(char **args);

//builtin/env.c
void		env_builtin(t_data *data);

//builtin/pwd.c
void		pwd_builtin(void);

//error.c
void		ft_error(char *str);

//parsing/minisplit.c
char		**mini_split(char *s, char c);

//parsing/parsing.c
void		init_parsing(char *line);
t_cmdgrp	*init_cmdgrp(char *line);
int			find_redir(char *str);
//void		parse_redir(t_cmdgrp *node);
char		*removechar(char *str, char c);
int			delchar(char **str, int pos, char c);
char		*clean_arg(char *str);
void		parse_exec(t_cmdgrp *node);
void		parse_redexec(t_cmdgrp *node);
void		parse_on_pipe(t_cmdgrp *node);
int			find_pipe(char *str);

//test.c
void	print_node(t_cmdgrp *node);
#endif