#include "../../inc/minishell.h"

/*
 * Executes the internal "echo" command.
 *
 * This function displays the passed arguments after processing options and quotes.
 * It handles the "-n" option which suppresses the trailing newline.
 *
 * @param args Pointer to a /////t_command///// structure containing the command's arguments.
 *
 * @return void. The function does not return a value.
 */
void	echo_builtin(char **args)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (args[i])
	{
		while (args[i] && (ft_strncmp_exact(args[i], "-n", 2) == 0))
		{
			i++;
			flag = 1;
		}
		while (args[i])
		{
			printf("%s", args[i]);
			i++;
			if (args[i])
				printf(" ");
		}
	}
	if (flag == 0)
		printf("\n");
}
