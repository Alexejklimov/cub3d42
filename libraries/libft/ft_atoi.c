/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:25:42 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 15:39:40 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_atoi(const char *nptr)
{
	size_t	i;
	size_t	acc;
	size_t	sign;

	i = 0;
	acc = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++ ;
	if (nptr[i] == '-')
	{
		sign = -sign;
		i++ ;
	}
	else if (nptr[i] == '+')
		i++ ;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		acc = acc * 10 + (nptr[i] - 48);
		i++ ;
	}
	return (acc * sign);
}

// #include <stdlib.h>
// #include <stdio.h>

// int	main(void)
// {
// 	const char		*test1 = "-+23232323";
// 	const char		*test2 = "-23";
// 	const char		*test3 = "-q2";
// 	const char		*test4 = "23 23";
// 	const char		*test5 = "--23232323";

// 	printf("%d--->%d\n", ft_atoi(test1), atoi(test1));
// 	printf("%d--->%d\n", ft_atoi(test2), atoi(test2));
// 	printf("%d--->%d\n", ft_atoi(test3), atoi(test3));
// 	printf("%d--->%d\n", ft_atoi(test4), atoi(test4));
// 	printf("%d--->%d\n", ft_atoi(test5), atoi(test5));

// 	return (0);
// }
