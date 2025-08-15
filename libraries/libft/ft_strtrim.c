/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:45:53 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 18:55:15 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static	int	is_char_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen((char *)s1);
	while (s1[start] && is_char_in_set(s1[start], set))
		start++;
	while (end > start && is_char_in_set(s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

// #include <stdio.h>
// int main()
// {
// 	const char	*str1 = "   Hello, World!   ";
// 	const char	*set = " ";

// 	char *trimmed = ft_strtrim(str1, set);
// 	if (trimmed)
// 	{
// 		printf("Original: '%s'\n", str1);
// 		printf("Trimmed: '%s'\n", trimmed);
// 		free(trimmed);
// 	}
// 	else
// 	{
// 		printf("Error: Memory allocation failed.\n");
// 	}
// 	const char *str2 = "***Hello, World!***";
// 	const char *set2 = "*";
// 	char *trimmed2 = ft_strtrim(str2, set2);
// 	if (trimmed2)
// 	{
// 		printf("Original: '%s'\n", str2);
// 		printf("Trimmed: '%s'\n", trimmed2);
// 		free(trimmed2);
// 	}
// 	else
// 	{
// 		printf("Error: Memory allocation failed.\n");
// 	}
// 	return (0);
// }