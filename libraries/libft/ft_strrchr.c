/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:51:03 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/30 12:58:19 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen((char *)s);
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)s + i);
		}
		i--;
	}
	return (NULL);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char *s1 = "qweq";
// 	printf("test null --> %p\n", NULL);
// 	printf("wer --> %s\n", ft_strrchr(s1, 'w'));
// 	printf("not in s --> %s\n", ft_strrchr(s1, 'a'));
// 	printf("double --> %s\n", ft_strrchr(s1, 'q'));
// 	printf("end of s -->      %p\n", ft_strrchr(s1, '\0'));
// 	printf("end of s test --> %p\n", (char *)(s1 + 4));
// 	return (0);
// }