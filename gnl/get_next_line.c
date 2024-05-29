/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:49:32 by asaux             #+#    #+#             */
/*   Updated: 2023/11/08 19:10:59 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extract_clear(char **stash)
{
	char	*new;
	char	*temp;
	int		i;

	i = 0;
	temp = *stash;
	if (!*stash)
		return (NULL);
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	new = ft_strndup_gnl(temp, i);
	*stash = ft_strndup_gnl(temp + i, ft_strlen_gnl(temp + i));
	free(temp);
	return (new);
}

char	*ft_free_str(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*str;
	int			ncl;

	ncl = 1;
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd < 0)
		return (ft_free_str(&stash));
	if (ft_strchr_gnl(stash, '\n'))
		return (ft_extract_clear(&stash));
	str = malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	while (ncl > 0 && !ft_strchr_gnl(stash, '\n'))
	{
		ncl = read(fd, str, BUFFER_SIZE);
		str[ncl] = 0;
		stash = ft_strjoin_gnl(stash, str);
	}
	ft_free_str(&str);
	return (ft_extract_clear(&stash));
}

/* #include <fcntl.h>
#include <stdio.h>
int    main(void)
{
	char    *content;
	int fd = open("text.txt", O_RDONLY);
	
	content = get_next_line(fd);
	while (ft_strlen_gnl(content))
	{
		printf("content : %s", content);
		free(content);
		content = get_next_line(fd);
	}
	close(fd);
	return (0);
} */