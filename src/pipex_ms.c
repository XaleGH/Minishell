#include "../inc/minishell.h"

void	init_pipe(char **args, t_data *data)
{
	int	fd[2];
	int	pid;
	int status;

	if (pipe(fd) == -1)
	{
		perror("pipe init error");
		exit (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	else if (!pid)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]); //
		execute_ms(args, data);
		exit(1);//
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);//
	}
}

int	pipex(int nbcmd, t_cmdgrp *node, t_data *data)
{
	int	i;

	i = 1;
	while (i < nbcmd)
	{
		init_pipe(node->part1->arg, data);
		node = node->part2;
		i++;
	}
	execute_ms(node->arg, data);
	while (wait(NULL) > 0);
	return (0);
}