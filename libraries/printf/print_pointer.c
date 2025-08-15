/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:42:02 by oklimov           #+#    #+#             */
/*   Updated: 2024/11/06 15:25:28 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*make_string(unsigned long val, int *len)
{
	int				i;
	unsigned long	tmp;
	char			*str;

	i = 0;
	tmp = val;
	if (val == 0)
	{
		*len = 1;
		str = ft_calloc(2, sizeof(char));
		str[0] = '0';
		return (str);
	}
	while (tmp != 0)
	{
		tmp = tmp / 16;
		i++;
	}
	str = ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (NULL);
	*len = i;
	return (str);
}

static void	convert_to_hex(unsigned long *tmp, char *out, int *i, int asc)
{
	while (*tmp != 0)
	{
		if ((*tmp % 16) < 10)
			out[*i] = (*tmp % 16) + '0';
		else
			out[*i] = (*tmp % 16) + asc;
		(*tmp) = (*tmp) / 16;
		(*i)--;
		if (*i < 0)
			break ;
	}
}

int	print_pointer(unsigned long val, int asc)
{
	unsigned long	tmp;
	char			*out;
	int				i;
	int				len;

	tmp = val;
	out = make_string(val, &len);
	if (!out)
		return (0);
	if (val == 0)
	{
		print_string("(nil)");
		free(out);
		return (5);
	}
	i = len - 1;
	convert_to_hex(&tmp, out, &i, asc);
	print_string("0x");
	print_string(out);
	free(out);
	return (len + 2);
}
