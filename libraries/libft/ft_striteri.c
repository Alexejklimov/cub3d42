/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:27:56 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 18:04:22 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}

// #include <stdio.h>

// void my_fun(unsigned int index, char *c)
// {
//     if (*c >= 'a' && *c <= 'z') {
//         *c = *c - 32;
//     }
//     printf("Index: %u, Character: %c\n", index, *c);
// }

// int main()
// {
// 	char str[] = "world!";

// 	printf("Origin: %s\n", str);
// 	ft_striteri(str, my_fun);
// 	printf("Modified: %s\n", str);

// 	return (0);
// }
