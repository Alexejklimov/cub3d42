/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:04:30 by oklimov           #+#    #+#             */
/*   Updated: 2024/11/06 15:07:25 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(const char *input, ...);
int		print_char(char c);
int		print_hex(unsigned int val, int asc);
int		print_integer(int n);
int		print_pointer(unsigned long val, int asc);
int		print_string(char *s);
int		print_unsigned(unsigned int num);
size_t	ft_strlen(const char	*s);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
