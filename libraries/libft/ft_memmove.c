/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:57:36 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 17:02:34 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	d = (char *)dest;
	s = (char *)src;
	if (d > s)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	else
	{
		while (i < n)
		{
			d[i] = s [i];
			i++;
		}
	}
	return (dest);
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char	src[] = "Hello, World!";
// 	char	dest[20];

// 	ft_memmove(dest, src, strlen(src) + 1);
// 	printf("Source: %s\n", src);
// 	printf("Dest: %s\n", dest);
// 	char	overlap[] = "abcdef";
// 	printf("Before: %s\n", overlap);
// 	ft_memmove(overlap + 2, overlap, 4);
// 	printf("After(overlap): %s\n", overlap);

// 	return (0);
// }