/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:31:59 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/30 13:25:33 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;
	void	*tmp2;

	if (!lst || !del || !f)
		return (NULL);
	tmp = NULL;
	while (lst)
	{
		tmp2 = f(lst->content);
		new = ft_lstnew(tmp2);
		if (!new)
		{
			del(tmp2);
			ft_lstclear(&tmp, del);
			return (NULL);
		}
		ft_lstadd_back(&tmp, new);
		lst = lst->next;
	}
	new->next = NULL;
	return (tmp);
}

// #include <stdio.h>
// void	del(void *content)
// {
// 	free(content);
// }

// void *double_int(void *data)
// {
// 	int	*new_data = malloc(sizeof(int));
//     if (new_data)
// 	{
// 		*new_data = (*(int *)data) * 2;
// 	}
// 	return (new_data);
// }

// int main()
// {
// 	int *data1 = malloc(sizeof(int));
// 	*data1 = 1;
// 	int *data2 = malloc(sizeof(int));
// 	*data2 = 2;
// 	int *data3 = malloc(sizeof(int));
// 	*data3 = 3;
// 	t_list *head = ft_lstnew(data1);
// 	head->next = ft_lstnew(data2);
// 	head->next->next = ft_lstnew(data3);
// 	t_list *new_list = ft_lstmap(head, double_int, del);

// 	t_list *current = new_list;
// 	while (current)
// 	{
// 		printf("%d\n", *(int *)current->content);
// 		current = current->next;
// 	}

// 	ft_lstclear(&head, del);
// 	ft_lstclear(&new_list, del);
// 	return (0);
// }
