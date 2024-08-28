/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:20:05 by asaux             #+#    #+#             */
/*   Updated: 2024/08/25 15:39:27 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Checks if a given position in a string is within quotes.
 *
 * This function determines if a specific character position in the input string
 * is within double quotes, single quotes, or not within any quotes, based on 
 * the `check_type` parameter. It returns different values depending on the type
 * of quotes enclosing the position:
 * - 0: Not within quotes
 * - 1: Within single quotes
 * - 2: Within double quotes
 *
 * @param str Pointer to the input string to be checked.
 * @param poschar The character position in the string to be checked.
 * @param check_type Determines the type of quote checking 
 * (0 for standard quotes, non-zero for argument-specific quote checking).
 *
 * @return int. Returns 2 if the position is within double quotes, 1 if within 
 * single quotes, and 0 if not within any quotes.
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
		if (check_type == 0 || check_type == 1)
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
 * Toggles the state of single and double quotes based on the input character.
 *
 * This function updates the states of single and double quotes based on the 
 * encountered character. It toggles the `squote` (single quote) and `dquote`
 * (double quote) flags to reflect whether the current character is inside 
 * quotes. It handles the transitions between quotes by switching the flags 
 * on encountering matching quote characters.
 *
 * @param c The character to be checked and used to update the quote states.
 * @param squote Pointer to the integer flag indicating whether single quotes
 * are currently open (1) or closed (0).
 * @param dquote Pointer to the integer flag indicating whether double quotes
 *  are currently open (1) or closed (0).
 *
 * @return void. The function does not return a value.
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
	else if (c == '\'' && !*dquote)
	{
		if (*squote == 1)
			*squote = 0;
		else
			*squote = 1;
	}
}

/*
 * Updates the state of single and double quotes based on the current and 
 * next characters.
 *
 * This function modifies the states of single and double quotes based on the 
 * current character and the next character in the string. It toggles the 
 * `squote` (single quote) and `dquote` (double quote) flags to reflect whether
 * the current character is inside quotes. The function also considers the next
 * character to determine if the quote should be closed 
 * (e.g., if it is a separator or end of string).
 *
 * @param c The current character being processed.
 * @param next_c The next character in the string to help decide if 
 * the quote should be closed.
 * @param squote Pointer to the integer flag indicating whether single quotes 
 * are currently open (1) or closed (0).
 * @param dquote Pointer to the integer flag indicating whether double quotes 
 * are currently open (1) or closed (0).
 *
 * @return void. The function does not return a value.
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
