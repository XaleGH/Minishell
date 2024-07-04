/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:03:17 by asaux             #+#    #+#             */
/*   Updated: 2024/07/04 14:58:04 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		input = readline("minishell > ");
		exec = ft_split(input, ' ');
		//init_parsing(input);
		execute_ms(exec, &data);
	}
	free_array(data.env);
}
