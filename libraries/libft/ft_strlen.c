/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:00:54 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 15:10:25 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strlen(const char	*s)

{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++ ;
	}
	return (i);
}
/*
#include <>
int	main()

{
	char *c;
	int	i;

	c = "Salut";
	i = ft_strlen(c);
!	pf("%d", i);
	return(0);
}
*/
