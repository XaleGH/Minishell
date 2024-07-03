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

	i = 0;
	if (args[1][i])
	{
		if (ft_strncmp(args[1], "-n", 2) == 0)
			printf("%s", args[2]);
		else
			printf("%s\n",args[1]);
	}
}