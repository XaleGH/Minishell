/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:09:57 by asaux             #+#    #+#             */
/*   Updated: 2024/08/28 09:41:33 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * Initializes a pipe for inter-process communication between two commands.
 *
 * This function sets up a pipe and forks a new process. The parent process and
 * child process are configured to use the pipe for communication. The child
 * process executes the given command with its output directed to the pipe,
 * while the parent process reads from the pipe.
 *
 * @param node A pointer to the command group node that contains the command to
 * execute.
 * @param data A pointer to the shell data structure containing the environment
 * and other information.
 *
 * This function performs the following steps:
 * 1. Creates a pipe using the `pipe` system call.
 * The pipe will have two file descriptors:
 *    - `fd[0]` for reading from the pipe.
 *    - `fd[1]` for writing to the pipe.
 * 2. Forks a new process using the `fork` system call.
 * 3. In the child process:
 *    - Closes the read end of the pipe (`fd[0]`).
 *    - Redirects the standard output (`STDOUT_FILENO`) to the write end of
 * the pipe (`fd[1]`).
 *    - Closes the write end of the pipe (`fd[1]`).
 *    - Executes the command specified by the `node` using `execute_ms`.
 *    - Exits the child process with status 0.
 * 4. In the parent process:
 *    - Closes the write end of the pipe (`fd[1]`).
 *    - Redirects the standard input (`STDIN_FILENO`) to the read end of
 * the pipe (`fd[0]`).
 *    - Closes the read end of the pipe (`fd[0]`).
 *
 * Error handling:
 * - If the `pipe` or `fork` system calls fail, an error message is printed
 * using `perror`, and the program exits with status 1.
 */
void	init_pipe(t_cmdgrp *node, t_data *data)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return (ft_printf("pipe init error"), exit (1));
	pid = fork();
	if (pid == -1)
		return (ft_printf("fork error"), exit (1));
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

/*
 * Sets up and executes a series of commands connected by pipes.
 *
 * This function manages the execution of multiple commands where the output of
 * one command is used as the input for the next command. It sets up pipes
 * between each command and ensures proper redirection of input and output.
 * After executing all commands, it restores the original standard input and
 * output file descriptors.
 *
 * @param nbcmd The number of commands to execute.
 * @param node A pointer to the command group node containing the commands to
 * execute.
 * @param data A pointer to the shell data structure containing the environment
 * and other information.
 *
 * The function performs the following steps:
 * 1. Duplicates the current standard input and output file descriptors using
 * `dup`.
 *    This is done to restore them later after the commands have been executed.
 * 2. Iterates through the list of commands (up to `nbcmd - 1`):
 *    - Calls `init_pipe` to set up the pipe and fork the process for the
 * current command.
 *    - Moves to the next command in the list.
 * 3. Executes the last command in the list directly using `execute_ms`.
 * 4. Restores the original standard input and output file descriptors using
 * `dup2`.
 * 5. Closes the duplicated file descriptors to free up resources.
 *
 * @return 0 on success.
 */
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
	while (wait(NULL) > 0)
		;
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	return (0);
}
