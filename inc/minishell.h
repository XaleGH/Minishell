/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:03:50 by asaux             #+#    #+#             */
/*   Updated: 2024/08/25 17:17:35 by asaux            ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

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
	char				**env;
	int					exit_status;
	struct s_cmdgrp 	*save_node;
}	t_data;

typedef enum s_tokentype
{
	EXEC,
	PIPE,
	IN_REDIR,
	OUT_REDIR,
	HEREDOC,
	DEFAULT
}	t_tokentype;

typedef struct s_cmdgrp
{
	int				type;
	struct s_cmdgrp	*part1;
	struct s_cmdgrp	*part2;
	char			*str;
	char			**arg;
	int				fd;
}	t_cmdgrp;

/* Fonctions */

//main.c
int			check_command(char *input);
int			nb_cmd(t_cmdgrp *node);
void		prompt_launch(char *input, t_data *data, t_cmdgrp *firstnode);
int			main(int ac, char **av, char **env);

//signal.c
void		handle_signals(void);
void		sigint(int signum);
void		sigquit(int signum);

//env.c
void		addshlvl(t_data *data);
int			search_row(t_data *data, char *str);
void		edit_shlvl(t_data *data, int value, int row);
char		**dupenv(char **env);

//execute.c
void		execute_ms(t_cmdgrp *node, t_data *data);
int			ft_strncmp_exact(char *s1, char *s2, int n);
int			exec_cmd(char **cmd, t_data *data);
void		redir_out(t_cmdgrp *node, t_data *data);
void		redir_in(t_cmdgrp *node, t_data *data);

//execute2.c
char		*extract_path(char **env);
char		*get_path(char **cmd, char **env, t_path *path);
char		*real_pathfind(char **cmd, char **env, char *pathfind);
int			is_builtin(char *str);
void		exec_builtin(char **str, t_data *data);

//utils.c
int			ft_isalldigit(char *str);
void		free_array(char **env);
int			ft_strlen_array(char **array);
char		**rm_from_array(char **array, int i);
int			ignore_w_space(char *str);

//pipex_ms.c
int			pipex(int nbcmd, t_cmdgrp *node, t_data *data);
void		init_pipe(t_cmdgrp *node, t_data *data);

//free.c
void		free_nodes(t_cmdgrp *node);
void		free_node_content(t_cmdgrp *node);
void		parsing_error(t_cmdgrp *firstnode, int code, char c);

//test.c
void		print_node(t_cmdgrp *node);

//bultins/cd.c
int			cd_builtin(char **args, t_data *data);
void		actu_env(char *dir, char *var, t_data *data);
int			go_home(t_data *data);
int			switch_dir(char *path);
char		*get_home(t_data *data);

//builtins/echo.c
void		echo_builtin(char **args, t_data *data);
int			echo_option(char *str);

//builtins/env.c
void		env_builtin(t_data *data);

//builtins/pwd.c
void		pwd_builtin(t_data *data);

//builtins/unset.c
void		unset_builtin(char **args, t_data *data);

//builtins/export.c
void		export_builtin(char **args, t_data *data);
char		**add_var_env(char **env, char *arg);
char		*recover_arg(char *arg);
int			check_arg(char *arg);

//builtins/export_sort_env.c
char		**sort_env(char **env);
void		sort_and_print_export(t_data *data);

//builtins/exit.c
int			exit_builtin(char **args, t_data *data);

//parsing/minisplit.c
int			mini_countword(char *s, char c);
char		*mini_strldup(char *s, int len);
int			mini_countchar(char *s, char c);
char		**mini_split(char *s, char c);
char		*get_word(char *s, int *i, char c);

//parsing/parsing.c
t_cmdgrp	*init_parsing(char *line, t_data *data);
t_cmdgrp	*init_cmdgrp(char *line, int len);
int			parse_redexec(t_cmdgrp *node, t_cmdgrp *firstnode, t_data *data);

//parsing/utils_parsing.c
int			is_separator(char c);
int			delchar(char **str, int pos, char c);
char		*clean_arg(char *str);
void		apply_all_clean(char **str, int *i);
char		check_syn_redir(t_cmdgrp *node, int i);

//parsing/quote_parsing.c
int			btwn_quote(char *str, int poschar, int check_type);
void		checkquote(char c, int *squote, int *dquote);
void		checkquote_arg(char c, char next_c, int *squote, int *dquote);

//parsing/redir_parsing.c
int			parse_redir(t_cmdgrp *node, int i, t_cmdgrp *firstnode);
int			is_redir_token(char c);
void		redir_open(t_cmdgrp *node, int i, int type);
int			heredoc(char *stopword);
int			heredoc_close(int fd);

//parsing/pipe_parsing.c
int			parse_on_pipe(t_cmdgrp *node, t_cmdgrp *firstnode, t_data *data);
int			find_pipe(char *str);

//parsing/env_replace.c
char		**env_replace(char **arg, t_data *data);
char		*replace_env_in_arg(char *arg, t_data *data);
int			replace_nothing(char **arg, int i);
int			replace_lexit(char **arg, int i, t_data *data);
int			replace_var(char **arg, int i, t_data *data);

#endif