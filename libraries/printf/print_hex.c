/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:41:45 by oklimov           #+#    #+#             */
/*   Updated: 2024/11/04 12:27:21 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static char	*make_zero_string(int *len)
{
	char	*str;

	*len = 0;
	str = malloc(2);
	if (str)
	{
		str[0] = '0';
		str[1] = '\0';
	}
	return (str);
}

static char	*make_string(unsigned int val, int *len)
{
	char			*str;
	int				i;
	unsigned int	tmp;

	i = 0;
	tmp = val;
	if (val == 0)
		return (make_zero_string(len));
	while (tmp != 0)
	{
		tmp /= 16;
		i++;
	}
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	*len = i - 1;
	return (str);
}

int	print_hex(unsigned int val, int asc)
{
	unsigned int	tmp;
	char			*out;
	int				len;

	tmp = val;
	out = make_string(val, &len);
	if (!out)
		return (0);
	if (val == 0)
		out[0] = '0';
	while (tmp != 0)
	{
		if ((tmp % 16) < 10)
			out[len] = (tmp % 16) + '0';
		else
			out[len] = (tmp % 16) + asc;
		tmp /= 16;
		len--;
	}
	ft_putstr_fd(out, 1);
	len = ft_strlen(out);
	free(out);
	return (len);
}
