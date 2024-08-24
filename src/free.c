/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:59:58 by asaux             #+#    #+#             */
/*   Updated: 2024/08/24 15:05:09 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * Recursively frees the memory allocated for a command group and its associated
 * nodes.
 *
 * This function takes a pointer to a `t_cmdgrp` structure and recursively frees
 * the memory allocated for the command group and its associated nodes. It first
 * frees the memory of the child nodes (if they exist) before freeing the memory
 * for the current node itself. The type of the node determines if it has child
 * nodes (when type == 1).
 *
 * The function assumes that `free_node_content` is responsible for freeing the
 * content of the command group node (e.g., strings and other dynamically
 * allocated data within the node).
 *
 * @param node A pointer to the `t_cmdgrp` structure that represents the command
 * group to be freed. If the node is a composite node (type == 1), its child
 * nodes (part1 and part2) will be recursively freed before freeing the node
 * itself.
 */
void	free_nodes(t_cmdgrp *node)
{
	if (node->type == 1)
	{
		free_nodes(node->part1);
		free_nodes(node->part2);
	}
	free_node_content(node);
	free(node);
}

/*
 * Frees the memory allocated for the content of a command group node.
 *
 * This function releases the memory allocated for the content of a `t_cmdgrp`
 * structure, specifically freeing the `str` and `arg` members if they are not
 * NULL. The `str` member typically holds a string that should be freed, while
 * `arg` is an array of strings that should be deallocated using the
 * `free_array` function.
 *
 * @param node A pointer to the `t_cmdgrp` structure whose content is to be
 * freed. This function does not free the `t_cmdgrp` structure itself, only
 * its internal content.
 */
void	free_node_content(t_cmdgrp *node)
{
	if (node->str != NULL)
		free(node->str);
	if (node->arg != NULL)
		free_array(node->arg);
}

/*
 * Handles and reports syntax or file-related errors during parsing.
 *
 * This function is used to handle and report errors encountered during the
 * parsing of a command line. Depending on the error code provided, it will
 * print an appropriate error message to standard output and free all allocated
 * resources associated with the parsing operation.
 *
 * @param firstnode A pointer to the first `t_cmdgrp` node in the parsing
 * process.
 * This node and all its descendants will be freed if an error occurs.
 * @param code An integer code indicating the type of error:
 * - 0: Syntax error (e.g., unexpected token).
 * - 1: File-related error (e.g., failure to create or open a file).
 * @param c A character associated with the error, such as the unexpected token
 * or problematic character that caused the error.
 *
 * This function first frees all resources associated with the parsing process
 * by calling `free_nodes` on `firstnode`. It then prints an error message
 * based on the error code provided:
 * - If `code` is 0, it reports a syntax error with the specific token.
 * - If `code` is 1, it reports a file-related error with the specific token.
 */
void	parsing_error(t_cmdgrp *firstnode, int code, char c)
{
	free_nodes(firstnode);
	if (code == 0)
		printf("minishell: syntax error near unexpected token '%c'\n", c);
	if (code == 1)
		printf("minishell: create or open file near token '%c'\n", c);
}
