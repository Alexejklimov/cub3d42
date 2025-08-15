/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:18:56 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 17:38:51 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
		ptr[i++] = (unsigned char)c;
	return (s);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char	str[50];

// 	strcpy(str, "Hello, World!");
// 	printf("Before memset: %s\n", str);

// 	ft_memset(str, '*', 5);
// 	printf("After memset: %s\n", str);

// 	strcpy(str, "Goodbye, World!");
// 	printf("Before memset: %s\n", str);

// 	ft_memset(str + 9, '#', 6);
// 	printf("After memset: %s\n", str);

// 	return (0);
// }