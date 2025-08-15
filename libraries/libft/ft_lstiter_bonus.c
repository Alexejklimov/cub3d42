/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:31:44 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 19:30:57 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// void	print_content(void *content)
// {
// 	printf("%d ", *(int *)content);
// }
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
// 	printf("ft_lstiter: ");
// 	ft_lstiter(list, print_content);
// 	ft_lstclear(&list, del);
// 	return (0);
// }
