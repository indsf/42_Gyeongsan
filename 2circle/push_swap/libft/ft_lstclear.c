/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-06 09:52:46 by inhlee            #+#    #+#             */
/*   Updated: 2025-04-06 09:52:46 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*plst;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		plst = (*lst)->next;
		del((*lst)->content);
		free((*lst));
		*lst = plst;
	}
}
