/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:25:19 by asaux             #+#    #+#             */
/*   Updated: 2024/08/25 10:18:44 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Parses and handles redirection operators in a command group.
 *
 * This function processes redirection operators ('>' and '<') within a command
 * group. It determines whether the redirection is for output or input, and 
 * handles each case accordingly. For output redirections, it calls `redir_open`
 * with the appropriate mode. For input redirections, it either sets the type 
 * to `HEREDOC` and calls `heredoc`, or handles simple redirection. It also 
 * removes the processed redirection tokens and their associated arguments 
 * from the command arguments.
 *
 * @param node Pointer to a `t_cmdgrp` structure representing the current 
 * command group being parsed.
 * @param i The index of the redirection operator in the command 
 * arguments array.
 * @param firstnode Pointer to the first `t_cmdgrp` structure, used for 
 * error reporting.
 *
 * @return int Returns 1 if parsing was successful, or 0 if an error occurred.
 */
int	parse_redir(t_cmdgrp *node, int i, t_cmdgrp *firstnode)
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
	if (node->fd == -1)
		return (parsing_error(firstnode, 1, node->arg[i][0]), 0);
	if (node->type != HEREDOC)
		node->arg = rm_from_array(node->arg, i + 1);
	node->arg = rm_from_array(node->arg, i);
	return (1);
}

/*
 * Handles the opening of files for redirection in a command group.
 *
 * This function opens a file for redirection based on the specified type of 
 * redirection (`OUT_REDIR` or `IN_REDIR`).
 * It sets the file descriptor for the redirection and handles different types
 * of file opening modes:
 * - Append mode (`O_APPEND`)
 * - Read-only mode (`O_RDONLY`)
 * - Truncate mode (`O_TRUNC`)
 * If no file is specified for the redirection, it sets the file descriptor to 
 * `-200` to indicate no file.
 * The function also ensures that any previously opened file descriptor is 
 * closed before opening a new one.
 *
 * @param node Pointer to a `t_cmdgrp` structure representing the current 
 * command group where redirection is being handled.
 * @param i The index in the command arguments array where the redirection 
 * operator is located.
 * @param type An integer indicating the type of redirection:
 * - `1` for output redirection with append mode,
 * - `2` for input redirection,
 * - `0` for output redirection with truncate mode.
 *
 * @return void. The function does not return a value.
 */
void	redir_open(t_cmdgrp *node, int i, int type)
{
	char	*file;

	if (node->arg[i + 1])
		file = clean_arg(node->arg[i + 1]);
	node->type = OUT_REDIR;
	if (type == 1)
		type = O_RDWR | O_CREAT | O_APPEND;
	else if (type == 2)
	{
		type = O_RDONLY;
		node->type = IN_REDIR;
	}
	else
		type = O_RDWR | O_CREAT | O_TRUNC;
	if (node->fd > 2)
		close(node->fd);
	if (node->arg[i + 1])
		node->fd = open(file, type, 0777);
}

/*
 * Handles the creation and writing of a here-document file.
 *
 * This function creates a temporary file named "here_doc" and writes lines to
 * it until a line matching the specified stopword is entered. The file is 
 * opened with read and write permissions, truncating any existing content.
 * The function reads input lines from the user and writes them to the file.
 * If the input line matches the stopword, the function closes the file and 
 * returns.
 *
 * @param stopword The string used to terminate the here-document input.
 * Input lines are compared against this stopword, and if a match is found,
 * the here-document input process is completed.
 *
 * @return Returns `-1` if the file cannot be created, `1` if the input is 
 * closed prematurely, or `0` on successful completion of writing and closing
 * the file.
 */
int	heredoc(char *stopword)
{
	char	*line;
	int		file;

	line = NULL;
	file = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (file == -1)
		return (-1);
	while (1)
	{
		line = readline("here_doc >");
		if (!line)
			return (1);
		if (ft_strlen(stopword) == ft_strlen(line)
			&& ft_strncmp(line, stopword, ft_strlen(stopword)) == 0)
			return (free(line), heredoc_close(file));
		ft_putstr_fd(line, file);
		ft_putchar_fd('\n', file);
		free(line);
	}
}

/*
 * Closes the current here-document file descriptor and reopens the file
 * for reading.
 *
 * This function closes the file descriptor for the currently open "here_doc"
 * file and reopens the file in read-only mode. The file is opened with read
 * permissions.
 *
 * @param fd The file descriptor of the currently open "here_doc" file to be
 * closed.
 *
 * @return Returns the new file descriptor for the reopened "here_doc" file.
 */
int	heredoc_close(int fd)
{
	close(fd);
	fd = open("here_doc", O_RDONLY, 0777);
	return (fd);
}

/*
 * Checks if a character is a redirection token.
 *
 * This function determines whether the provided character is a redirection 
 * token, which in this context are the characters '>' and '<'.
 *
 * @param c The character to be checked.
 *
 * @return Returns 1 if the character is a redirection token ('>' or '<'), 
 * otherwise returns 0.
 */
int	is_redir_token(char c)
{
	return (c == '>' || c == '<');
}
