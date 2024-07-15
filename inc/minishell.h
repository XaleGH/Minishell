
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
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

//Struct

typedef struct s_data
{
	char	**env;
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

//env.c
void		addshlvl(t_data *data);
int			search_row(t_data *data, char *str);
void		edit_shlvl(t_data *data, int value, int row);
char		**dupenv(char **env);

//utils.c
int			ft_isalldigit(char *str);
void		free_array(char **env);
int			ft_strlen_array(char **array);
char		**rm_from_array(char **array, int i);

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
int			mini_countword(char *s, char c);
char		*mini_strldup(char *s, int len);
int			mini_countchar(char *s, char c);
char		**mini_split(char *s, char c);
char		*get_word(char *s, int *i, char c);

//parsing/parsing.c
void		init_parsing(char *line);
t_cmdgrp	*init_cmdgrp(char *line, int len);
void		parse_redexec(t_cmdgrp *node);

/* parsing/utils_parsing.c */
int			is_separator(char c);
char		*removechar(char *str, char c);
int			delchar(char **str, int pos, char c);
char		*clean_arg(char *str);
void		apply_all_clean(char **str, int *i);

/* parsing/quote_parsing.c */
int			btwn_quote(char *str, int poschar,int check_type);
void		checkquote(char c, int *squote, int *dquote);
void		checkquote_arg(char c ,char next_c, int *squote, int *dquote);

/* parsing/redir_parsing.c */
void		parse_redir(t_cmdgrp *node, int i);
int			is_redir_token(char c);
void		redir_open(t_cmdgrp *node, int i, int type);
int			heredoc(char *stopword);
int			heredoc_close(int fd);

/* parsing/pipe_parsing.c */
void		parse_on_pipe(t_cmdgrp *node);
int			find_pipe(char *str);

/* parsing/exec_parsing.c */
//void		parse_exec(t_cmdgrp *node);

//test.c
void		print_node(t_cmdgrp *node);

#endif