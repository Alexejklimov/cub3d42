/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:39:56 by nmagomad          #+#    #+#             */
/*   Updated: 2025/09/15 17:22:39 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_game *game)
{
	int	i;
	int	j;
	int	player_size;

	player_size = game->minimap.scale / 2;
	if (player_size < 1)
		player_size = 1;
	if (player_size > 3)
		player_size = 3;
	i = -player_size;
	while (i <= player_size)
	{
		j = -player_size;
		while (j <= player_size)
		{
			if ((i * i + j * j) <= 4)
				put_pixel(game->image, game->minimap.player.x + j,
					game->minimap.player.y + i, create_color(255, 0, 0, 255));
			j++;
		}
		i++;
	}
}

void	draw_block(t_game *game, int start_x, int start_y, uint32_t color)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->minimap.scale)
	{
		y = 0;
		while (y < game->minimap.scale)
		{
			if (start_x + x < game->minimap.x + game->minimap.size
				&& start_y + x < game->minimap.y + game->minimap.size)
			{
				put_pixel(game->image, start_x + x, start_y + y, color);
			}
			y++;
		}
		x++;
	}
}

void	draw_map(t_game *game)
{
	int			x;
	int			y;
	int			start_x;
	int			start_y;
	uint32_t	color;

	x = 0;
	while (x < game->map_height)
	{
		y = 0;
		while (y < game->map_width)
		{
			if (game->map[x][y] == 1)
				color = create_color(58, 58, 58, 255);
			else
				color = create_color(150, 150, 150, 255);
			start_x = game->minimap.x + x * game->minimap.scale;
			start_y = game->minimap.y + y * game->minimap.scale;
			draw_block(game, start_x, start_y, color);
			y++;
		}
		x++;
	}
}

t_point	update_line_position(t_point start, t_point d, t_point s, int *err)
{
	int	e2;

	e2 = 2 * (*err);
	if (e2 > -d.y)
	{
		*err -= d.y;
		start.x += s.x;
	}
	if (e2 < d.x)
	{
		*err += d.x;
		start.y += s.y;
	}
	return (start);
}

void	draw_line(t_game *game, t_point start, t_point end, uint32_t color)
{
	t_point	d;
	t_point	s;
	int		err;

	d.x = abs(end.x - start.x);
	d.y = abs(end.y - start.y);
	if (start.x < end.x)
		s.x = 1;
	else
		s.x = -1;
	if (start.y < end.y)
		s.y = 1;
	else
		s.y = -1;
	err = d.x - d.y;
	while (1)
	{
		put_pixel(game->image, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		start = update_line_position(start, d, s, &err);
	}
}
