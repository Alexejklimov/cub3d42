/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:41:54 by oklimov           #+#    #+#             */
/*   Updated: 2024/11/05 15:03:26 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_integer(int n)
{
	int				num;
	unsigned int	i;

	num = n;
	i = 1;
	if (n == -2147483648)
	{
		ft_putnbr_fd(n, 1);
		return (11);
	}
	if (n < 0 && n != -2147483648)
	{
		num = -n;
		i++;
	}
	while (num > 9)
	{
		num = num / 10;
		i++;
	}
	ft_putnbr_fd(n, 1);
	return (i);
}
