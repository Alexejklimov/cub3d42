/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:27:18 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 16:20:11 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (size--)
		str[size] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char		*dst;
	int			count;
	int			i;
	long int	nbr;

	nbr = n;
	count = count_size(nbr);
	i = 0;
	if (nbr < 0 || count == 0)
		count++;
	dst = ft_strnew(count);
	if (!dst)
		return (NULL);
	if (nbr < 0)
	{
		nbr = -nbr;
		dst[0] = '-';
		i++;
	}
	while (count > i)
	{
		dst[--count] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (dst);
}

// #include <stdio.h>

// int main(void)
// {
// 	int		numbers[] = {0, 42, -42, 123456, -123456, 2147483647, -2147483648};
// 	char	*result;
// 	int		i = 0;

// 	while (i < sizeof(numbers) / sizeof(numbers[0]))
// 	{
// 		result = ft_itoa(numbers[i]);
// 		if (result)
// 		{
// 			printf("Integer: %d, String: %s\n", numbers[i], result);
// 			free(result);
// 		}
// 		else
// 		{
// 			printf("malloc sucks in: %d\n", numbers[i]);
// 		}
// 		i++;
// 	}
// 	return (0);
// }