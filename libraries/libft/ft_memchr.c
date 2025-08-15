/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:59:05 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 16:31:59 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memchr( const void *s, int c, size_t n )
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include "libft.h"

// int	main(void)
// {
// 	const char	*str = "Hello, world!";
// 	char		*result;

// 	result = ft_memchr(str, 'w', 13);
// 	if (result)
// 	{
// 		printf("'w' -->: %ld\n", result - str);
// 	}
// 	else
// 	{
// 		printf("w nema\n");
// 	}
// 	result = ft_memchr(str, 'o', 13);
// 	if (result)
// 	{
// 		printf("o -->: %ld\n", result - str);
// 	}
// 	else
// 	{
// 		printf("'o' nema\n");
// 	}
// 	result = ft_memchr(str, 'x', 13);
// 	if (result)
// 	{
// 		printf("x -->: %ld\n", result - str);
// 	}
// 	else
// 	{
// 		printf("'x' nema\n");
// 	}
// }