/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:55:55 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 16:36:44 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s1 + i) != *(unsigned char *)(s2 + i))
		{
			return (*(unsigned char *)(s1 + i)
			- *(unsigned char *)(s2 + i));
		}
		i++;
	}
	return (0);
}

// #include <stdio.h>
// int	main()
// {
// 	const char	*s1 = "qwert";
// 	const char	*s2 = "qwert";
// 	const char	*s3 = "qwe";
// 	const char	*s4 = "qw";

// 	printf("%d\n", ft_memcmp(s1, s2, 5));
// 	printf("%d\n", ft_memcmp(s1, s3, 5));
// 	printf("%d\n", ft_memcmp(s1, s4, 5));
// 	printf("%d\n", ft_memcmp(s1, s4, 1));

// 	return (0);
// }