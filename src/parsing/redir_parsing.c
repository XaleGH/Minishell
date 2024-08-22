#include "../../inc/minishell.h"

void	parse_redir(t_cmdgrp *node, int i)
{
	if (node->arg[i][0] == '>')
	{	
		if (node->arg[i][1])
			redir_open(node, i, 1);
		else
			redir_open(node, i, 0);
	}
	else if (node->arg[i][0] == '<')
	{
		if (node->arg[i][1])
		{
			node->type = HEREDOC;
			node->fd = heredoc(node->arg[i + 1]);
		}
		else
			redir_open(node, i, 2);
	}
	if (node->type != HEREDOC)
		node->arg = rm_from_array(node->arg, i + 1);
	node->arg = rm_from_array(node->arg, i);
}

void	redir_open(t_cmdgrp *node, int i, int type)
{
	char	*file;

	file = clean_arg(node->arg[i + 1]);
	node->type = IN_REDIR;
	if (type == 1)
		type = O_RDWR | O_CREAT | O_APPEND;
	else if (type == 2)
	{
		type = O_RDONLY;
		node->type = OUT_REDIR;
	}
	else
		type = O_RDWR | O_CREAT | O_TRUNC;
	if (node->fd > 2)
		close(node->fd);
	node->fd = open(file, type, 0777);
	if (node->fd == -1)
	{
		;//error // open error
	}
}

int	heredoc(char *stopword)
{
	char	*line;
	int		file;

	line = NULL;
	file = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (file == -1)
	{
		;//error create /open heredoc
	}
	while (1)
	{
		line = readline("here_doc >");
		if (!line)
			return (1);
		if (ft_strlen(stopword) == ft_strlen(line) 
			&& ft_strncmp(line, stopword, ft_strlen(stopword)) == 0)
			return (free(line), heredoc_close(file));
		ft_putstr_fd(line, file);
		free(line);
	}
}
int	heredoc_close(int fd)
{
	close(fd);
	fd = open("here_doc", O_RDONLY, 0777);
	if (fd == -1)
	{
		;//error open heredoc
	}
	return (fd);
}


int	is_redir_token(char c)
{
	return(c == '>' || c == '<');
}
