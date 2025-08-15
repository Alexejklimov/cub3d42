/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:42:26 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/22 15:43:42 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

// #include <stdio.h>

// int	main(void)

// {
// 	char	i;
// 	char test = '\n';

// 	i = ft_isdigit(test);
// 	ntf("%d\n", i);
// 	return (0);
// }
