/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:29:44 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 19:24:10 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

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
// 	ft_lstadd_front(&list, ft_lstnew(value1));
// 	ft_lstadd_front(&list, ft_lstnew(value2));
// 	ft_lstadd_front(&list, ft_lstnew(value3));

// 	printf("List: ");
// 	ft_lstprint(list);
// 	return (0);
// }
