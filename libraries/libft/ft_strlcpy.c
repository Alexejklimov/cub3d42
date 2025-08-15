/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:34:32 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 15:09:51 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)

{
	size_t	i;
	size_t	acc;

	acc = 0;
	while (src[acc] != '\0')
	{
		acc++ ;
	}
	if (size == 0)
	{
		return (acc);
	}
	i = 0;
	while (src[i] != '\0' && i < (size -1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (acc);
}

// #include <stdio.h>

// int	main(void)

// {
// 	char	src[] = "serus!";
// 	char	dest[10];

// 	printf("%d\n%s\n", ft_strlcpy(dest, src, 3), dest);
// 	return (0);	
// }
