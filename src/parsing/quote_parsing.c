#include "../../inc/minishell.h"

/*
 * Search if the given pos of string is between simple or double quotes.
 *
 * return 1 if the pos given is between simple or double quotes.
 *
 * @param char	pointer to the string.
 * @param int	position in the string.
 * @param int 	type of check.
 *
 * @return int. return 1 if it's between simple quote
 * 2 if it's between double quote 0 if it is not.
 */

int	btwn_quote(char *str, int poschar, int check_type)
{
	int	dquote;
	int	squote;
	int	i;

	i = -1;
	dquote = 0;
	squote = 0;
	while (str[++i])
	{
		if (check_type == 0)
			checkquote(str[i], &squote, &dquote);
		else
			checkquote_arg(str[i], str[i + 1], &squote, &dquote);
		if (i == poschar && (dquote || squote))
		{
			if (dquote)
				return (2);
			return (1);
		}
	}
	return (0);
}

/*
 * Search if the given pos of char is between simple or double quotes.
 *
 * set 1 in squote and dquote pointer if the pos given is between
 * simple or double quotes, 0 if isnt.
 *
 * @param char	char to test.
 * @param int*	pointer on simple quote flag.
 * @param int*	pointer on double quote flag.
 *
 * @return void doesn't return anything.
 */
void	checkquote(char c, int *squote, int *dquote)
{
	if (c == '"' && !*squote)
	{
		if (*dquote == 1)
			*dquote = 0;
		else
			*dquote = 1;
	}
	else if (c == '\'' && !dquote)
	{
		if (*squote == 1)
			*squote = 0;
		else
			*squote = 1;
	}
}

/*
 * Search if the given pos of char is between simple or double quotes.
 *
 * set 1 in squote and dquote pointer if the pos given is between
 * simple or double quotes and it can be consider as a new arg, 0 if isnt.
 *
 * @param char	char to test.
 * @param char	next char ine the string.
 * @param int*	pointer on simple quote flag.
 * @param int*	pointer on double quote flag.
 *
 * @return void doesn't return anything.
 */
void	checkquote_arg(char c, char next_c, int *squote, int *dquote)
{
	if (c == '"' && !(*squote))
	{
		if (*dquote == 1 && (is_separator(next_c) || !next_c))
			*dquote = 0;
		else
			*dquote = 1;
	}
	else if (c == '\'' && !(*dquote))
	{
		if (*squote == 1 && (is_separator(next_c) || !next_c))
			*squote = 0;
		else
			*squote = 1;
	}
}
