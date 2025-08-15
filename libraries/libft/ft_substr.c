/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:10:19 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 19:00:13 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (start + len > ft_strlen((char *)s))
		len = ft_strlen((char *)s) - start;
	if (start >= ft_strlen((char *)s))
	{
		str = (char *)malloc(1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

// #include <stdio.h>
// int main()
// {
// 	const char	*original = "Hello, World!";

// 	char *substr1 = ft_substr(original, 7, 5);
// 	if (substr1)
// 	{
// 		printf("Substring 1: '%s'\n", substr1);
// 		free(substr1);
// 	}
// 	else
// 	{
// 		printf("Mem alloc failed\n");
// 	}
// 	char *sub1 = ft_substr(original, 5, 20);
// 	if (sub1)
// 	{
// 		printf("Sub1: '%s'\n", sub1);
// 		free(sub1);
// 	}
// 	else
// 	{
// 		printf("Mem allocfailed\n");
// 	}

// 	return (0);
// }
