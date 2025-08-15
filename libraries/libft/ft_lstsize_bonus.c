/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:29:59 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/30 13:40:04 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*tmp;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
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
