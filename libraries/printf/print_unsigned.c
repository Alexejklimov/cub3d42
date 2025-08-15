/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:42:21 by oklimov           #+#    #+#             */
/*   Updated: 2024/11/04 12:00:05 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printout(unsigned int num)
{
	if (num > 9)
		print_unsigned(num / 10);
	if (num <= 9)
	{
		ft_putchar_fd(num + 48, 1);
		return ;
	}
	ft_putchar_fd((num % 10) + 48, 1);
}

int	print_unsigned(unsigned int num)
{
	unsigned int	i;

	printout(num);
	i = 1;
	while (num > 9)
	{
		num = num / 10;
		i++;
	}
	return (i);
}
