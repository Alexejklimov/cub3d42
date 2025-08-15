/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:08:12 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 18:21:07 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len >= size)
		return (src_len + size);
	i = dst_len;
	j = 0;
	while (src[j] != '\0' && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst_len + src_len);
}

// #include <stdio.h>
// int	main()
// {
// 	char	dest[10];
// 	printf("%ld\n", ft_strlcat(dest, "qwertyyyy", 11));
// 	printf("%ld\n", ft_strlcat(dest, "qwe", 5));
// 	printf("%ld\n", ft_strlcat(dest, "qwert", 2));
// 	printf("%ld\n", ft_strlcat(dest, "qwert", 0));
// 	return (0);
// }