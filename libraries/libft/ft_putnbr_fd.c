/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:28:47 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 17:52:55 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	num;

	num = n;
	if (num == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num = -num;
		ft_putnbr_fd(num, fd);
	}
	else if (num > 9)
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putnbr_fd(num % 10, fd);
	}
	else
	{
		ft_putchar_fd(num + '0', fd);
	}
}
// int	main()
// {
// 	ft_putnbr_fd(1234567, 1);
// 	ft_putnbr_fd(-2147483648, 1);
// 	return (0);
// }