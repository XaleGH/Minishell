/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:38:44 by asaux             #+#    #+#             */
/*   Updated: 2023/10/16 17:11:54 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*temp;

	if (!lst)
		return (0);
	temp = ft_lstnew((*f)(lst->content));
	if (!temp)
		return (NULL);
	list = temp;
	lst = lst->next;
	while (lst)
	{
		temp->next = ft_lstnew((*f)(lst->content));
		if (!temp->content)
		{
			ft_lstclear(&list, (*del));
			return (0);
		}
		temp = temp->next;
		lst = lst->next;
	}
	return (list);
}
