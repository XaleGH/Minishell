/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:33:06 by asaux             #+#    #+#             */
/*   Updated: 2024/08/26 16:02:49 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Checks if a character is a separator.
 *
 * This function determines whether the provided character is considered a 
 * separator in the context of command parsing. The separators include space,
 * pipe, and redirection operators.
 *
 * @param c The character to be checked.
 *
 * @return Returns 1 if the character is a separator (' ', '|', '<', or '>'),
 * otherwise returns 0.
 */
int	is_separator(char c)
{
	return (c == ' ' || c == '|' || c == '<' || c == '>');
}

/*
 * Deletes a character from a string at a specified position.
 *
 * This function removes a character from a string at the given position, 
 * provided that the character at that position matches the specified character.
 * The function reallocates memory for the string without the specified 
 * character and updates the pointer to the new string.
 *
 * @param str Pointer to a string from which the character will be removed.
 * @param pos The position in the string where the character to be removed 
 * is located.
 * @param c The character to be removed from the string.
 *
 * @return Returns 1 if the character was successfully removed; otherwise,
 * returns 0.
 */
int	delchar(char **str, int pos, char c)
{
	char	*newstr;
	int		i;
	int		j;

	if (str[0][pos] == c)
	{
		newstr = malloc(sizeof(char) * (ft_strlen(str[0])));
		i = 0;
		j = 0;
		while (str[0][i])
		{
			if (i != pos)
				newstr[j++] = str[0][i];
			i++;
		}
		newstr[j] = '\0';
		free(str[0]);
		str[0] = newstr;
		return (1);
	}
	return (0);
}

/*
 * Cleans a given argument string by removing specific characters.
 *
 * This function processes the input string to remove certain characters based
 * on their context within quotes. It duplicates the input string for processing
 * and removes single and double quotes when they are not within quotes.
 * It also applies additional cleaning operations through a helper function.
 *
 * @param str The input string to be cleaned.
 *
 * @return Returns the cleaned string with specified characters removed.
 */
char	*clean_arg(char *str)
{
	int		i;
	int		j;
	char	*dupstr;

	dupstr = ft_strdup(str);
	i = 0;
	j = 0;
	while (dupstr[j])
	{
		if (btwn_quote(dupstr, j, 0) == 1)
		{
			if (delchar(&str, i, '\'') != 1)
				i++;
		}
		else if (btwn_quote(dupstr, j, 0) == 2)
		{
			if (delchar(&str, i, '"') != 1)
				i++;
		}
		else
			apply_all_clean(&str, &i);
		j++;
	}
	free(dupstr);
	return (str);
}

/*
 * Applies a series of cleaning operations to the given string.
 *
 * This function performs multiple cleaning operations on the string, removing
 * specific characters: single quotes, double quotes, and spaces. It updates
 * the index pointer to reflect the position within the string after each 
 * operation.
 *
 * @param str Pointer to the string that will be cleaned.
 * @param i Pointer to the index position within the string. This index is
 * updated after each cleaning operation.
 *
 * @return void. The function does not return a value.
 */
void	apply_all_clean(char **str, int *i)
{
	if ((delchar(str, *i, '\'') != 1) && (delchar(str, *i, '"') != 1)
		&& (delchar(str, *i, ' ') != 1))
		(*i)++;
}

/*
 * Checks the syntax of a redirection operator in a command group.
 *
 * This function inspects the redirection operator at the specified position
 * in the command arguments and verifies its syntax. It handles cases of invalid
 * or incomplete redirection operators and checks if there is an issue with the
 * subsequent argument or if additional redirection characters are present.
 *
 * @param node Pointer to a t_cmdgrp structure representing the command group.
 * @param i Index in the argument list where the redirection operator is
 * located.
 *
 * @return Returns the redirection operator if there's a syntax error associated
 * with it, or 0 if the syntax is valid. If the redirection is incomplete or
 * improperly formatted, the function returns the problematic character or
 * operator.
 */
char	check_syn_redir(t_cmdgrp *node, int i)
{
	if (node->arg[i][0] == '>' || node->arg[i][0] == '<')
	{
		if (node->arg[i][0] == '>' && node->arg[i][1] && node->arg[i][1] != '>')
			return (node->arg[i][1]);
		else if (node->arg[i][0] == '<'
			&& node->arg[i][1] && node->arg[i][1] != '<')
			return (node->arg[i][1]);
		else if ((node->arg[i][0] == '>' || node->arg[i][0] == '<')
			&& !node->arg[i + 1])
			return (node->arg[i][0]);
		else if (node->arg[i + 1] && is_separator(node->arg[i + 1][0]))
			return (node->arg[i + 1][0]);
		else
			return (0);
	}
	else
		return (0);
}
