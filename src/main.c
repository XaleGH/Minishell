/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:03:17 by asaux             #+#    #+#             */
/*   Updated: 2024/08/17 00:55:02 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_command(char *input)
{
	if (input[0] == ' ' || input[0] == '\0')
		return (0);
	return (1);
}

int    main(int ac, char **av, char **env)
{
	t_data	data;
	char	*input;
	char	**exec;

	(void) av;
	if (ac > 1)
		return (printf("Error, no argument needed\n"),1);
	data.env = dupenv(env);
	addshlvl(&data);
	while (1)
	{
		input = readline("▶️  minishell > ");
		if (check_command(input))
			add_history(input);
		exec = ft_split(input, ' ');
		//init_parsing(input);
		execute_ms(exec, &data);
	}
	free_array(data.env);
}
