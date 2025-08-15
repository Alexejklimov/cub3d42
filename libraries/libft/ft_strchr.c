/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:33:38 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/23 17:37:42 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	if ((char)c == '\0')
		return ((char *)(s + ft_strlen((char *)s)));
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char *s1 = "qweq";
// 	printf("test null --> %p\n", NULL);
// 	printf("wer --> %s\n", ft_strchr(s1, 'w'));
// 	printf("not in s --> %s\n", ft_strchr(s1, 'a'));
// 	printf("double --> %s\n", ft_strchr(s1, 'q'));
// 	printf("end of s -->      %p\n", ft_strchr(s1, '\0'));
// 	printf("end of s test --> %p\n", (char *)(s1 + 4));
// 	return (0);
// }