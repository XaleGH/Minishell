
#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*input;

	(void) av;
	if (ac > 1)
		return (printf("Error, no argument needed\n"),1);
	data.env = dupenv(env);
	addshlvl(&data);
	free_array(data.env);
	input = readline("minishell > ");
	init_parsing(input);
}
