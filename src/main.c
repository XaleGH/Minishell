/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:03:17 by asaux             #+#    #+#             */
/*   Updated: 2024/08/24 15:45:54 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * Checks if the input command is valid (i.e., not empty or whitespace only).
 *
 * This function is used to determine whether the input string contains a valid
 * command.
 * A command is considered invalid if it is either empty or consists solely of
 * whitespace.
 *
 * @param input A pointer to the input string representing the command to check.
 *
 * @return 1 if the command is valid (not empty and not just whitespace),
 * 0 otherwise.
 * 
 * The function works by checking the first character of the input string:
 * - If the first character is a space or if the string is empty (`'\0'`),
 * it returns 0, indicating that the command is invalid.
 * - Otherwise, it returns 1, indicating that the command is considered valid.
 */
int	check_command(char *input)
{
	if (input[0] == ' ' || input[0] == '\0')
		return (0);
	return (1);
}

/*
 * Counts the number of commands in a command group separated by pipes.
 *
 * This function calculates the number of separate command segments in a command
 * group, where commands are divided by pipe (`|`) symbols. It starts from the
 * given command group node and traverses through all the nodes connected by
 * pipes, incrementing the count for each command segment found.
 *
 * @param node A pointer to the initial command group node from which to start
 * counting.
 *
 * @return The number of command segments in the command group.
 * 
 * The function initializes the count to 1 (assuming the initial node itself
 * is a valid command segment).
 * It then iterates through the nodes:
 * - While the current node's type is PIPE, it increments the count and moves
 * to the next node (the part2 of the current node).
 * - Once a node without a PIPE type is encountered, the function stops
 * iterating and returns the total count.
 */
int	nb_cmd(t_cmdgrp *node)
{
	int			i;
	t_cmdgrp	*temp;

	i = 1;
	temp = node;
	while (temp->type == PIPE)
	{
		i++;
		temp = temp->part2;
	}
	return (i);
}

/*
 * Processes and executes a command input from the user.
 *
 * This function is responsible for handling a user input command. It first
 * checks if the command is non-empty and adds it to the history if it is
 * valid. Then, it parses the input to create a command group structure.
 * Depending on the number of commands in the parsed structure, it either
 * executes them directly or pipes them through a series of commands. Finally,
 * it frees the allocated resources for the command group structure.
 *
 * @param input The user input command string to be processed.
 * @param data A pointer to the `t_data` structure containing environment
 * variables and other necessary data for executing commands.
 * @param firstnode A pointer to the `t_cmdgrp` structure representing the first
 * command group in the parsed input.
 *
 * @return void
 */
void	prompt_launch(char *input, t_data *data, t_cmdgrp *firstnode)
{
	if (check_command(input))
		add_history(input);
	firstnode = init_parsing(input, data);
	if (firstnode)
	{
		if (nb_cmd(firstnode) > 1)
			pipex(nb_cmd(firstnode), firstnode, data);
		else
			execute_ms(firstnode, data);
		free_nodes(firstnode);
	}
}

/*
 * Main function for the minishell program.
 *
 * This is the entry point of the minishell application. It initializes
 * necessary data structures, sets up signal handling, and enters an infinite
 * loop to read and process user input commands. The input is parsed, executed,
 * and appropriate actions are taken based on the parsed commands. The function
 * gracefully handles the case when the user decides to exit.
 *
 * @param ac The number of command-line arguments passed to the program.
 * @param av An array of command-line argument strings.
 * @param env An array of environment variable strings.
 *
 * @return An integer exit status: 0 for successful execution, or 1 if an error
 * occurs due to incorrect usage.
 */
int	main(int ac, char **av, char **env)
{
	t_data		data;
	char		*input;
	t_cmdgrp	firstnode;

	(void) av;
	if (ac > 1)
		return (printf("Error, no argument needed\n"), 1);
	data.env = dupenv(env);
	addshlvl(&data);
	handle_signals();
	rl_catch_signals = 0;
	while (1)
	{
		input = readline("▶️  minishell > ");
		if (input == NULL)
			return (printf("exit\n"), free(input), 0);
		else
			prompt_launch(input, &data, &firstnode);
		free(input);
	}
}
