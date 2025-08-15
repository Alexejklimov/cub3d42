/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:44:21 by oklimov           #+#    #+#             */
/*   Updated: 2025/07/24 12:07:24 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

char	*ft_strdup(const char *s)

{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[len] != '\0')
	{
		len++ ;
	}
	dest = malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++ ;
	}
	dest[i] = '\0';
	return (dest);
}
/*
#include <stdio.h>

int	main(int argc, char **argv)

{
	if (argc > 1)
	{
		printf("%s\n", ft_strdup(argv[1]));
	free(ft_strdup(argv[1]));
		return(0);
	}
}*/
