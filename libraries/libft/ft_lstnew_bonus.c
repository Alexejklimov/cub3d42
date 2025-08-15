/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:29:25 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/30 13:52:47 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*item_list;

	item_list = (t_list *)malloc(sizeof(t_list));
	if (!item_list)
		return (NULL);
	item_list->content = content;
	item_list->next = NULL;
	return (item_list);
}

// #include <stdio.h>
// int main()
// {
// 	int	*data = malloc(sizeof(int));
// 	if (!data)
// 	{
// 		return (0);
// 	}
// 	*data = 17;
// 	t_list *node = ft_lstnew(data);
// 	if (!node)
// 	{
// 		free(data);
// 		return (0);
// 	}
// 	printf("Node content: %d\n", *(int *)node->content);
// 	free(node->content);
// 	free(node);
// 	return (0);
// }