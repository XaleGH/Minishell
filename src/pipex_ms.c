#include "../inc/minishell.h"

void	init_pipe(t_cmdgrp *node, t_data *data)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return (perror("pipe init error"), exit (1));
	pid = fork();
	if (pid == -1)
		return (perror("fork error"), exit (1));
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_ms(node, data);
		exit(0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

int	pipex(int nbcmd, t_cmdgrp *node, t_data *data)
{
	int	i;
	int	stdin_copy;
	int	stdout_copy;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	i = 1;
	while (i < nbcmd)
	{
		init_pipe(node->part1, data);
		node = node->part2;
		i++;
	}
	execute_ms(node, data);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	return (0);
}
