/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:36:50 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 16:58:55 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (char *)dest;
	s = (char *)src;
	while (n-- > 0)
	{
		*d++ = *s++;
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char src[] = "Hello, World!";
// 	char dest[20];

// 	ft_memcpy(dest, src, strlen(src) + 1);
// 	printf("Source: %s\n", src);
// 	printf("Dest: %s\n", dest);
// 	return (0);
// }