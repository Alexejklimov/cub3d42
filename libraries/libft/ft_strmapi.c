/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:27:40 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 18:49:36 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret;
	unsigned int	i;

	if (!s || !f)
		return ((void *)0);
	ret = ft_strdup(s);
	if (!ret)
		return ((void *)0);
	i = 0;
	while (ret[i])
	{
		ret[i] = f(i, ret[i]);
		i++;
	}
	return (ret);
}

// #include <stdio.h>
// char my_transform(unsigned int index, char c)
// {
// 	index--;
//    return (c + 1);
// }

// int main()
// {
//     const char *original = "hello, world!";
//     char *modified;

//     modified = ft_strmapi(original, my_transform);

//     if (modified)
// 	{
//         printf("Original: %s\n", original);
//         printf("Modified: %s\n", modified);
//         free(modified);
//     }
// 	else
// 	{
//         printf("Error: Memory allocation failed.\n");
//     }

//     return (0);
// }
