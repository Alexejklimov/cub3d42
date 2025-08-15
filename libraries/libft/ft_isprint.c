/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:42:26 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/15 11:26:15 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_isprint(int c)

{
	if (!(c <= 126 && c >= 32))
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
	char test[] = "QQFHGDSFFDrrrr55555!";

	i = ft_str_is_printable(test);
!	pf("%d\n", i);
	return (0);
}*/
