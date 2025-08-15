/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:57:16 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 17:31:48 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)

{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++ ;
	}
	if (i < n)
	{
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

// 	printf("%d\n", ft_strncmp(s1, s2, 5));
// 	printf("%d\n", ft_strncmp(s1, s3, 5));
// 	printf("%d\n", ft_strncmp(s1, s4, 5));
// 	printf("%d\n", ft_strncmp(s1, s4, 1));

// 	return (0);
// }
