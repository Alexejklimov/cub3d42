/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:34:24 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/15 11:30:47 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_isalpha(int c)

{
	if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
	{
		return (0);
	}
	else
	{
		return (1);
	}
}
// #include <stdio.h>

// int	main(void)

// {
// 	char	test = '!';

// 	printf("%d\n", ft_isalpha(test));
// 	return (0);
// }
