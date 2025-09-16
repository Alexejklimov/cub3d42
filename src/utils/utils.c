/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:34:44 by nmagomad          #+#    #+#             */
/*   Updated: 2025/09/16 18:16:59 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_get_time(void)
{
	struct timeval	tv;
	double			time;

	time = 0;
	if (gettimeofday(&tv, NULL) == -1)
	{
		perror("error gettimeofday");
		exit (EXIT_FAILURE);
	}
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	panic(char *s)
{
	printf("%s\n", s);
	exit(1);
}

int	map_info_fill_checker(t_map_info *map)
{
	int	i;

	if (!map->start_orient)
		return (ft_printf("ERROR fill info %c", map->start_orient), 0);
	i = 0;
	while (i < 4)
	{
		if (!map->texture[i])
			return (ft_printf("ERROR fill info text"), 0);
		i++;
	}
	i = 0;
	return (1);
}

void	errexit(t_game *game, char *msg)
{
	cleanup(game);
	if (msg)
		printf("%s\n", msg);
	exit(1);
}
