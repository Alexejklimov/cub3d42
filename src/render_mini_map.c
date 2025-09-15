/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:50:04 by nmagomad          #+#    #+#             */
/*   Updated: 2025/09/15 17:22:01 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mini_map(t_game *game);
t_point	convert_to_minimap_coords(t_game *game, double x, double y);
void	draw_player(t_game *game);
void	draw_line(t_game *game, t_point start, t_point end, uint32_t color);
void	draw_map(t_game *game);

static void	run_dda_2d(t_game *game, t_raycast *r, double distance, double step)
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

void	draw_rays(t_game *game)
{
	t_raycast	r;
	int			i;
	double		ray_angle;
	double		step;
	double		distance;

	i = 0;
	while (i < MINI_MAP_RAYS)
	{
		r.camera_x = 2 * i / (double)MINI_MAP_RAYS - 1;
		ray_angle = game->player.angle + atan(r.camera_x * 0.8);
		r.raydir_x = cos(ray_angle);
		r.raydir_y = sin(ray_angle);
		r.dir_x = game->player.x;
		r.dir_y = game->player.y;
		step = 0.05;
		distance = 0.0;
		run_dda_2d(game, &r, distance, step);
		draw_line(game, game->minimap.player,
			convert_to_minimap_coords(game, r.dir_x, r.dir_y),
			create_color(0, 255, 0, 100));
		i++;
	}
}

void	render_mini_map(t_game *game)
{
	init_mini_map(game);
	draw_map(game);
	draw_player(game);
	draw_rays(game);
}
