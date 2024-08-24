/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:40:05 by asaux             #+#    #+#             */
/*   Updated: 2024/08/24 15:49:21 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * Sets up signal handlers for the minishell.
 *
 * This function configures custom signal handlers for the shell. It sets up the
 * `SIGINT` and `SIGQUIT` signals to be handled by the `sigint` and`sigquit`
 * functions, respectively. This ensures that the shell can appropriately
 * respond to these signals, such as when the user pressesCtrl+C or Ctrl+\.
 *
 * @return void
 */
void	handle_signals(void)
{
	signal(2, sigint);
	signal(3, sigquit);
}

/*
 * Signal handler for SIGINT (interrupt signal, typically sent by Ctrl+C).
 *
 * This function handles the SIGINT signal, which is commonly triggered by
 * pressing Ctrl+C. It performs the following actions:
 * 
 * 1. Checks if there are any child processes that need to be reaped by calling
 * `waitpid` with the `WNOHANG` option. This avoids blocking if there are no
 * child processes to wait for.
 * 2. If `waitpid` fails, it prints a "^C" message to indicate that the
 * interrupt signal was received.
 * 3. Resets the input line in the readline library to an empty string, prepares
 * the prompt for a new line, and redisplays the prompt to allow the user to
 * continue typing a new command.
 *
 * @param signum The signal number. This parameter is not used in the function.
 *
 * @return void
 */
void	sigint(int signum)
{
	(void)signum;
	if (waitpid(-1, NULL, WNOHANG) == -1)
	{
		printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
 * Signal handler for SIGQUIT (quit signal, typically sent by Ctrl+\).
 *
 * This function is a placeholder for handling the SIGQUIT signal. In its
 * current implementation, it does not perform any actions when SIGQUIT is
 * received.
 * 
 * SIGQUIT is typically sent by pressing Ctrl+\ and is often used to cause a
 * process to terminate and produce a core dump.
 *
 * @param signum The signal number. This parameter is not used in the function.
 *
 * @return void
 */
void	sigquit(int signum)
{
	(void) signum;
}
