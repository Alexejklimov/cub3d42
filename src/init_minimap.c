/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:49:51 by nmagomad          #+#    #+#             */
/*   Updated: 2025/09/15 17:21:10 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	convert_to_minimap_coords(t_game *game, double x, double y)
{
	t_point	p;

	p.x = game->minimap.x + (int)(x * game->minimap.scale);
	p.y = game->minimap.y + (int)(y * game->minimap.scale);
	return (p);
}

void	init_mini_map(t_game *game)
{
	int		scale_x;
	int		scale_y;
	float	percents;

	percents = 0.2f;
	game->minimap.max_size = (int)(SCREEN_WIDTH * percents);
	scale_x = game->minimap.max_size / game->map_width;
	scale_y = game->minimap.max_size / game->map_height;
	if (scale_x < scale_y)
		game->minimap.scale = scale_x;
	else
		game->minimap.scale = scale_y;
	if (game->minimap.scale < 1)
		game->minimap.scale = 1;
	game->minimap.mwidth = game->map_height * game->minimap.scale;
	game->minimap.mheight = game->map_width * game->minimap.scale;
	if (game->minimap.mwidth > game->minimap.mheight)
		game->minimap.size = game->minimap.mwidth;
	else
		game->minimap.size = game->minimap.mheight;
	game->minimap.x = SCREEN_WIDTH - game->minimap.mwidth - 10;
	game->minimap.y = 10;
	game->minimap.player = convert_to_minimap_coords(game, game->player.x,
			game->player.y);
}
