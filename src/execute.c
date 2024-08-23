#include "../inc/minishell.h"

int	exec_cmd(char **cmd, t_data *data)
{
	char	*pathfind;
	pid_t	pid;
	int		status;

	pathfind = NULL;
	pathfind = real_pathfind(cmd, data->env, pathfind);
	if (pathfind == NULL)
		return (0);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), exit(1), 0);
	else if (pid == 0)
	{
		if (execve(pathfind, cmd, data->env) == -1)
			return (free(pathfind), printf("exec error\n"), 0);
	}
	else
	{
		free(pathfind);
		if (waitpid(pid, &status, 0) == -1)
			return (perror("waitpid"), exit(1), 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
	}
	return (0);
}

int	ft_strncmp_exact(char *s1, char *s2, int n)
{
	int	i;

	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	i = 0;
	while ((s1[i] && i < n) || (s2[i] && i < n))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	redir_out(t_cmdgrp *node, t_data *data)
{
	int	stdout_copy;

	stdout_copy = dup(STDOUT_FILENO);
	dup2(node->fd, STDOUT_FILENO);
	node->type = EXEC;
	execute_ms(node, data);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);
}

void	redir_in(t_cmdgrp *node, t_data *data)
{
	int	stdin_copy;

	stdin_copy = dup(STDIN_FILENO);
	dup2(node->fd, STDIN_FILENO);
	node->type = EXEC;
	execute_ms(node, data);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
}

void	execute_ms(t_cmdgrp *node, t_data *data)
{
	if (node->type == EXEC)
	{
		if (!node->arg[0])
			return ;
		else if (is_builtin(node->arg[0]) == 0)
			exec_builtin(node->arg, data);
		else
			exec_cmd(node->arg, data);
	}
	if (node->type == IN_REDIR || node->type == HEREDOC)
		redir_in(node, data);
	if (node->type == OUT_REDIR)
		redir_out(node, data);
}
