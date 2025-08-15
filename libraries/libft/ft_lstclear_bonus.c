/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:31:20 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/30 13:05:41 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = tmp;
		}
	}
}

// void	del(void *content)
// {
// 	free(content);
// }

// #include <stdio.h>
// void	ft_lstprint(t_list *lst)
// {
// 	while (lst)
// 	{
// 		printf("%d -> ", *(int *)(lst->content));
// 		lst = lst->next;
// 	}
// 	printf("NULL\n");
// }

// int	main()
// {
// 	t_list	*list = NULL;

// 	int *value1 = malloc(sizeof(int));
// 	int *value2 = malloc(sizeof(int));
// 	int *value3 = malloc(sizeof(int));
// 	*value1 = 1;
// 	*value2 = 2;
// 	*value3 = 3;
// 	ft_lstadd_back(&list, ft_lstnew(value1));
// 	ft_lstadd_back(&list, ft_lstnew(value2));
// 	ft_lstadd_back(&list, ft_lstnew(value3));
// 	printf("List: ");
// 	ft_lstprint(list);
// 	ft_lstclear(&list, del);
// 	return (0);
// }
