/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:44:08 by asaux             #+#    #+#             */
/*   Updated: 2024/08/25 17:10:38 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * Executes a command using `execve` in a child process.
 *
 * This function finds the full path of the executable file for a given command,
 * forks a child process to execute the command, and waits for the child process
 * to complete. It also updates the exit status of the command in the `t_data`
 * structure.
 *
 * @param cmd An array of command arguments, with the first element being the
 * command itself and the subsequent elements being its arguments.
 * @param data A pointer to a `t_data` structure that contains the environment
 * variables and exit status.
 * @return Returns 0 on success. On failure, it prints an error message and
 * returns 0. It also handles errors in `fork`, `execve`, and `waitpid` by
 * printing corresponding error messages and terminating the process if
 * necessary.
 */
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

/*
 * Compares two strings for exact equality up to a specified length.
 *
 * This function compares two strings character by character up to a maximum of
 * `n` characters. It first checks if the lengths of the two strings are equal.
 * If they are not, it returns 1. If they are of equal length, it then compares
 * the strings up to `n` characters. The comparison stops as soon as a mismatch
 * is found or `n` characters have been compared. If the strings are equal up to
 * `n` characters, it returns 0. Otherwise, it returns the difference between
 * the mismatched characters.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @param n The maximum number of characters to compare.
 * @return Returns 0 if the strings are equal up to `n` characters. If the
 * strings differ, it returns the difference between the first pair of differing
 * characters (s1[i] - s2[i]). If the strings have different lengths,
 * it returns 1.
 */
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

/*
 * Redirects the standard output to a file and executes a command.
 *
 * This function performs output redirection by duplicating the standard output
 * file descriptor, redirecting the output to the file descriptor specified in
 * `node->fd`, and then executing a command. After execution, it restores the
 * original standard output and closes the duplicated file descriptor.
 *
 * @param node A pointer to a t_cmdgrp structure representing the command group.
 * It contains the file descriptor to which the output should be redirected.
 * @param data A pointer to a t_data structure containing environment data and
 * other relevant information needed for command execution.
 */
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

/*
 * Redirects the standard input from a file and executes a command.
 *
 * This function performs input redirection by duplicating the standard input
 * file descriptor, redirecting the input from the file descriptor specified
 * in `node->fd`, and then executing a command. After execution, it restores
 * the original standard input and closes the duplicated file descriptor.
 *
 * @param node A pointer to a t_cmdgrp structure representing the command group.
 * It contains the file descriptor from which the input should be read.
 * @param data A pointer to a t_data structure containing environment data and
 * other relevant information needed for command execution.
 */
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

/*
 * Executes a command or built-in command based on the type of node and
 * redirections.
 *
 * This function determines the type of command or redirection to perform based
 * on the `node` structure's type. It then executes the appropriate action:
 * - Executes a built-in command if the command is a built-in.
 * - Executes an external command if it's not a built-in.
 * - Handles input redirection (including heredocs) if specified.
 * - Handles output redirection if specified.
 *
 * @param node A pointer to a t_cmdgrp structure representing the command group.
 * It contains the type of command (e.g., EXEC, IN_REDIR, OUT_REDIR) and the
 * arguments to be executed.
 * @param data A pointer to a t_data structure containing environment data and
 * other relevant information needed for command execution.
 */
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
	else if (node->type == IN_REDIR || node->type == HEREDOC)
		redir_in(node, data);
	else if (node->type == OUT_REDIR)
		redir_out(node, data);
}
