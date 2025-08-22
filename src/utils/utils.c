/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:31:57 by oklimov           #+#    #+#             */
/*   Updated: 2025/08/22 11:33:22 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	clean_map_info(t_map_info *map_info)
{
	if (map_info->map)
		free_map(map_info->map);
	free(map_info);
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

double	ft_get_time()
{
	double	time = 0;
	struct timeval tv;
	
	
	if (gettimeofday(&tv, NULL) == -1)
	{
		perror("error gettimeofday");
		exit (EXIT_FAILURE);
	}
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}