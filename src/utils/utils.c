/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:31:57 by oklimov           #+#    #+#             */
/*   Updated: 2025/08/26 21:49:37 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	clean_map_info(t_map_info *map_info)
{
	if (map_info->map)
		free_map(map_info->map);
	free(map_info);
	exit (1);
}

void	free_map(char **map)
{
	int	y;

	if (map == NULL)
		return ;
	y = 0;
	while (map[y] != NULL)
	{
		free(map[y]);
		y++;
	}
	free(map);
}

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
	int i;

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
