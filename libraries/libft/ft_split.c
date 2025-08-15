/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:27:05 by oklimov           #+#    #+#             */
/*   Updated: 2024/10/29 14:35:59 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	**unleak(char **split, int j)
{
	while (j > 0)
	{
		free(split[j - 1]);
		j--;
	}
	free (split);
	return (NULL);
}

static int	count_words(char const *str, char c)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
			words++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (words);
}

static char	*write_word(char const *s, char c)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

static int	add_words(char **split, char const *s, char c, int j)
{
	split[j] = write_word(s, c);
	if (!split[j])
		return (0);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			if (!add_words(split, s + i, c, j++))
				return (unleak(split, j));
		}
		while (s[i] != c && s[i])
			i++;
	}
	split[j] = NULL;
	return (split);
}

// void	free_split(char **split)
// {
// 	int i = 0;

// 	if (!split)
// 		return ;
// 	while (split[i])
// 	{
// 		free(split[i]);
// 		split[i] = NULL;
// 		i++;
// 	}
// 	free(split);
// }
// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	char		**res;
// 	const char	*test = argv[1];
// 	char		sep = argv[2][0];
// 	int			i;
// 	(void)argc;

// 	res = ft_split(test, sep);
// 	printf("%d-->", count_words(test, sep));
// 	if (!res)
// 	{
// 		printf("Error: malloc sucks)))\n");
// 		return (1);
// 	}
// 	i = 0;
// 	while (res[i])
// 	{
// 		printf("res[%d] = \"%s\"\n", i, res[i] );
// 		i++;
// 	}
// 	free_split(res);
// 	return (0);
// }