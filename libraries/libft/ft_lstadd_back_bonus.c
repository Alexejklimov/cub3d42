/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:30:32 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 19:23:01 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (lst)
	{
		if (*lst == NULL)
		{
			*lst = new;
		}
		else
		{
			tmp = ft_lstlast(*(lst));
			tmp->next = new;
		}
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
// 	ft_lstadd_back(&list, ft_lstnew(value1));
// 	ft_lstadd_back(&list, ft_lstnew(value2));
// 	ft_lstadd_back(&list, ft_lstnew(value3));

// 	printf("List: ");
// 	ft_lstprint(list);
// 	return (0);
// }
