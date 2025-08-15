/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:32:36 by oklimov           #+#    #+#             */
/*   Updated: 2024/11/12 10:06:32 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	if (!nmemb || !size)
		return (malloc(0));
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (nmemb * size));
	return (ptr);
}

// void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	char	*ptr;
// 	size_t	n;

// 	if (!nmemb || !size)
// 		return (malloc(0));
// 	ptr = malloc(nmemb * size);
// 	if (!ptr)
// 		return (NULL);
// 	n = 0;
// 	while (n < nmemb * size)
// 		ptr[n++] = 0;
// 	return (ptr);
// }///////////////     without bzero
