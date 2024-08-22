/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:03:17 by asaux             #+#    #+#             */
/*   Updated: 2024/08/22 16:33:43 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_command(char *input)
{
	if (input[0] == ' ' || input[0] == '\0')
		return (0);
	return (1);
}

int	nb_cmd(t_cmdgrp *node)
{
	int i;
	t_cmdgrp *temp;

	i = 1;
	temp = node;
	while (temp->type == PIPE)
	{
		i++;
		temp = temp->part2;
	}
	return (i);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*input;
	t_cmdgrp *firstnode;

	(void) av;
	if (ac > 1)
		return (printf("Error, no argument needed\n"),1);
	data.env = dupenv(env);
	addshlvl(&data);
	while (1)
	{
		input = readline("▶️  minishell > ");
		//if (check_command(input))
			//add_history(input);
		firstnode = init_parsing(input);
		if (nb_cmd(firstnode) > 1)
			pipex(nb_cmd(firstnode), firstnode, &data);
		else
			execute_ms(firstnode->arg, &data);
		free(input);
		free_nodes(firstnode);
	}
	free_array(data.env);
}
