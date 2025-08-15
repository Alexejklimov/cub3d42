/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:42:26 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 14:59:25 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_isalnum(int c)

{
	if (!(c <= '9' && c >= '0')
		&& !(c >= 'a' && c <= 'z')
		&& !(c >= 'A' && c <= 'Z'))
	{
		return (0);
	}
	return (1);
}
/*
#include <>

int	main(void)

{
	int	i;
	char test[] = "24y242426664";

	i = ft_str_is_numeric(test);
!	pf("%d\n", i);
	return (0);
}*/
