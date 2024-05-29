/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:50:15 by asaux             #+#    #+#             */
/*   Updated: 2023/11/08 18:42:17 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char		*get_next_line(int fd);
char		*ft_strjoin_gnl(char *s1, char *s2);
char		*ft_extract_clear(char **stash);
char		*ft_free_str(char **str);
char		*ft_strndup_gnl(char *s1, int l);
int			ft_strlen_gnl(char *str);
int			ft_strchr_gnl(char *s, int c);

#endif