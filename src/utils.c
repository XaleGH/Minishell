
#include "../inc/minishell.h"

/*
 * check if the given string contain only digit character.
 *
 * @param char. Pointer on the string to be checked.
 *
 * @return int. The function return the row where the given string is find.
 */
int	ft_isalldigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
 * Free the given array .
 *
 * Free the memory allocated of the given array.
 *
 * @param char. pointer to the array.
 *
 * @return void. The function does not return a value.
 */
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

/*
 * Search if the given pos of string is between simple or double quotes.
 *
 * return 1 if the pos given is between simple or double quotes.
 *
 * @param char. pointer to the string.
 * @param int. position in the string.
 *
 * @return int. return 1 if it's between simple quote
 * 2 if it's between double quote 0 if it is not.
 */
int	btwn_quote(char *str, int poschar)
{
	int	dquote;
	int squote;
	int i;

	i = -1;
	dquote = 0;
	squote = 0;
	while (str[++i])
	{
		if (str[i] == '"' && !squote)
		{
			if (dquote == 1)
				dquote = 0;
			else 
				dquote = 1;
		}
		else if (str[i] == '\'' && !dquote)
		{
			if (squote == 1)
				squote = 0;
			else 
				squote = 1;
		}
		else if (i == poschar && (dquote || squote))
		{
			if (dquote)
				return(2);
			return (1);
		}
	}
	return (0);
}

/*
 * Search if the given pos of string is between simple or double quotes.
 *
 * return 1 if the pos given is between simple or double quotes.
 *
 * @param char. pointer to the string.
 * @param int. position in the string.
 *
 * @return int. return 1 if it's between simple quote 2
 * if it's between double quote 0 if it is not.
 */
int	is_quoted_arg(char *str, int poschar)
{
	int	dquote;
	int squote;
	int i;

	i = -1;
	dquote = 0;
	squote = 0;
	while (str[++i])
	{
		if (str[i] == '"' && !squote && (str[i + 1] == ' ' || !str[i + 1]))
		{
			if (dquote == 1)
				dquote = 0;
			else 
				dquote = 1;
		}
		else if (str[i] == '\'' && !dquote && (str[i + 1] == ' ' || !str[i + 1]))
		{
			if (squote == 1)
				squote = 0;
			else 
				squote = 1;
		}
		else if (i == poschar && (dquote || squote))
		{
			if (dquote)
				return(2);
			return (1);
		}
	}
	return (0);
}
