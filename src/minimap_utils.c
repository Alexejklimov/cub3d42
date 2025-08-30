/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:49:51 by nmagomad          #+#    #+#             */
/*   Updated: 2025/08/30 16:04:04 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	game->minimap.x = SCREEN_WIDTH - game->minimap.mheight - 50;
	game->minimap.y = 10;
	game->minimap.player = convert_to_minimap_coords(game, game->player.x,
			game->player.y);
}

void	run_dda_2d(t_game *game, t_raycast *r, double distance, double step)
{
	while (distance < 7)
	{
		r->dir_x += (r->raydir_x * step);
		r->dir_y += (r->raydir_y * step);
		distance += step;
		r->map_x = (int)r->dir_x;
		r->map_y = (int)r->dir_y;
		if (r->map_x < 0 || r->map_x >= game->minimap.mwidth
			|| r->map_y < 0 || r->map_y >= game->minimap.mheight
			|| game->map[r->map_x][r->map_y] == 1)
		{
			break ;
		}
	}
}
