/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:29:37 by oklimov           #+#    #+#             */
/*   Updated: 2024/11/07 16:14:26 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

static char	*ft_strchr(const char *s, int c)
{
	int		i;

	if ((char)c == '\0')
		return ((char *)(s + ft_strlen((char *)s)));
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	return (NULL);
}

static int	check_type(const char *type, va_list args)
{
	int	i;

	i = 0;
	if (*type == 'c')
		i += print_char(va_arg(args, int));
	else if (*type == 's')
		i += print_string(va_arg(args, char *));
	else if (*type == 'p')
		i += print_pointer(va_arg(args, unsigned long), 87);
	else if (*type == 'd')
		i += print_integer(va_arg(args, int));
	else if (*type == 'i')
		i += print_integer(va_arg(args, int));
	else if (*type == 'u')
		i += print_unsigned(va_arg(args, unsigned int));
	else if (*type == 'x')
		i += print_hex(va_arg(args, unsigned int), 87);
	else if (*type == 'X')
		i += print_hex(va_arg(args, unsigned int), 55);
	else
		return (-1);
	return (i);
}

int	ft_printf(const char *input, ...)
{
	va_list			args;
	unsigned int	i;

	i = 0;
	va_start(args, input);
	while (*input != '\0')
	{
		if (*input == '%')
		{
			input++;
			if (*input == '%')
				i += print_char('%');
			else if (ft_strchr("cspdiuxX", *input))
				i += check_type(input, args);
			else
				return (va_end(args), -1);
		}
		else
			i += print_char(*input);
		input++;
	}
	va_end(args);
	return (i);
}
