/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:35:49 by asaux             #+#    #+#             */
/*   Updated: 2023/10/16 16:53:00 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*l;

	if (!*lst)
		return ;
	while (*lst)
	{
		l = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = l;
	}
}
