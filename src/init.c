/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:35:04 by nmagomad          #+#    #+#             */
/*   Updated: 2025/08/21 18:18:54 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


int	init(t_game *game)
{
	size_t	i;
	size_t	j;
	

	game->DEBUG_FLAG = 0;

	printf("%d, %d\n", game->map_info->start_pos[0], game->map_info->start_pos[1]);
	if (game->map_info->start_pos[0])
		game->player.x = game->map_info->start_pos[0];
	game->player.y = game->map_info->start_pos[1];
	/*
	*	dirX	dirY	planeX	planeY	- dircection
	*	-1		 0		0		0.66		left
	*	 1		 0		0		0.66		right
	*	 0		-1		0.66	0			up
	*	 0		 1		0.66	0			down
	**/
	game->player.dx = -1;
	game->player.dy = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
	game->oldtime = 0;
	game->map_width = game->map_info->y;
	game->map_height = game->map_info->x;
	
	game->map = malloc(game->map_info->x * sizeof(int *));
	if (!game->map)
	{
		perror("out of memory");
		return (-1);
	}
	game->map[0] = malloc(game->map_info->x * game->map_info->y * sizeof(int));
	if (!game->map[0])
	{
		perror("out of memory");
		return (-1);
	}
	i = 1;
	while (i < game->map_info->x)
	{
		game->map[i] = game->map[0] + i * game->map_info->y;
		i++;
	}
	i = 0;
	while (i < game->map_info->x)
	{
		j = 0;
		while (j < game->map_info->y)
		{

			if (game->map_info->map[i][j] == '1')
				game->map[i][j] = 1;
			else
				game->map[i][j] = 0;
			j++;
		}
		i++;
	}

	return (0);
}