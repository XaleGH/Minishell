#include "../inc/minishell.h"

/*
 * Handles errors by printing an error message and exiting the program.
 *
 * This function sets the errno to 1, prints the provided error message along with the error description,
 * and then exits the program with a status code of 1.
 *
 * @param str Pointer to a string containing the error message to be printed.
 *
 * @return void. The function does not return a value.
 */
void	ft_error(char *str)
{
	errno = 1;
	perror(str);
	exit(1);
}
