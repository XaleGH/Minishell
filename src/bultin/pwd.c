#include "../../inc/minishell.h"

/*
 * Executes the internal "pwd" command.
 *
 * This function prints the current working directory to standard output.
 *
 * @return void. The function does not return a value.
 */
void	pwd_builtin(void)
{
	char *path;

	path = NULL;
	path = getcwd(path, 0);
	if (!path)
		ft_error("no pwd");
	printf("%s", path);
	free(path);
}
