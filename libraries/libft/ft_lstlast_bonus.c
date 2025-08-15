/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:30:15 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/30 13:10:11 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (lst)
		while (tmp->next)
			tmp = tmp->next;
	return (tmp);
}

// #include <stdio.h>
// t_list	*create_node(void *content)
// {
// 	t_list	*new_node = (t_list *)malloc(sizeof(t_list));
// 	if (!new_node)
// 	{
// 		return (NULL);
// 	}
// 	new_node->content = content;
// 	new_node->next = NULL;
// 	return (new_node);
// }

// int	main()
// {
// 	int *data1 = malloc(sizeof(int));
// 	*data1 = 1;
// 	int *data2 = malloc(sizeof(int));
// 	*data2 = 2;
// 	int *data3 = malloc(sizeof(int));
// 	*data3 = 3;

// 	t_list *head = create_node(data1);
// 	head->next = create_node(data2);
// 	head->next->next = create_node(data3);

// 	t_list *last = ft_lstlast(head);
// 	if (last)
// 	{
// 		printf("The last node's content is: %d\n", *(int *)last->content);
//     }
// 	else
// 	{
// 		printf("The list is empty.\n");
// 	}
// 	while (head)
// 	{
// 		t_list *tmp = head;
// 		head = head->next;
// 		free(tmp->content);
// 		free(tmp);
//     }
//     return (0);
// }