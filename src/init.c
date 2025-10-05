/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:35:04 by nmagomad          #+#    #+#             */
/*   Updated: 2025/10/05 18:18:18 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int	allocate_map(t_game *game)
{
	int	i;

	if (!game)
		return (-1);
	game->map = malloc(game->map_height * sizeof(int *));
	if (!game->map)
	{
		perror("out of memory");
		return (-1);
	}
	game->map[0] = malloc(game->map_width * game->map_height * sizeof(int));
	if (!game->map[0])
	{
		perror("out of memory");
		free(game->map);
		return (-1);
	}
	i = 1;
	while (i < game->map_height)
	{
		game->map[i] = game->map[0] + i * game->map_width;
		i++;
	}
	return (0);
}

static void	convert_map_to_int(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_width)
	{
		j = 0;
		while (j < game->map_height)
		{
			if (game->map_info->map[i][j] == '1')
				game->map[j][i] = 1;
			else
				game->map[j][i] = 0;
			j++;
		}
		i++;
	}
}

/*
 * | Directions  | dirX | dirY | planeX | planeY |
 * | ----------- | ---- | ---- | ------ | ------ |
 * | **N**       | 0    | -1   | 0.66   | 0      |
 * | **S**       | 0    | 1    | -0.66  | 0      |
 * | **E**       | 1    | 0    | 0      | 0.66   |
 * | **W**       | -1   | 0    | 0      | -0.66  |
*/
static	void	init_direction(t_game *game)
{
	char		dir;
	t_camera	direction[256];

	if (!game || !game->map_info)
		panic("Error: Pointer `game or man_info` is NULL");
	ft_memset(&direction, 0, sizeof(direction));
	dir = game->map_info->start_orient;
	direction['N'] = (t_camera){0, -1, 0.66, 0};
	direction['S'] = (t_camera){0, 1, -0.66, 0};
	direction['E'] = (t_camera){1, 0, 0, 0.66};
	direction['W'] = (t_camera){-1, 0, 0, -0.66};
	if (direction[(int)dir].dirx || direction[(int)dir].diry
		|| direction[(int)dir].planex || direction[(int)dir].planey)
	{
		game->player.dx = direction[(int)dir].dirx;
		game->player.dy = direction[(int)dir].diry;
		game->player.plane_x = direction[(int)dir].planex;
		game->player.plane_y = direction[(int)dir].planey;
	}
	else
		panic("Error: orientation of spwning is rong");
	game->player.angle = atan2(game->player.dy, game->player.dx);
}

static void	init_ceiling_floor_color(t_game *game)
{
	int	r;
	int	g;
	int	b;

	if (!game || !game->map_info)
		panic("Error: Pointer `game or man_info` is NULL");
	r = game->map_info->ceil_rgb[0];
	g = game->map_info->ceil_rgb[1];
	b = game->map_info->ceil_rgb[2];
	game->ceil_color = create_color(r, g, b, 255);
	r = game->map_info->floor_rgb[0];
	g = game->map_info->floor_rgb[1];
	b = game->map_info->floor_rgb[2];
	game->floor_color = create_color(r, g, b, 255);
}

int	init(t_game *game)
{
	if (game->map_info->start_pos[0])
		game->player.y = game->map_info->start_pos[0] + 0.5;
	if (game->map_info->start_pos[1])
		game->player.x = game->map_info->start_pos[1] + 0.5;
	game->oldtime = 0;
	game->map_width = (int)game->map_info->x;
	game->map_height = (int)game->map_info->y;
	init_direction(game);
	init_ceiling_floor_color(game);
	if (allocate_map(game) != 0)
	{
		clean_map_info(game->map_info);
		free(game);
		return (-1);
	}
	convert_map_to_int(game);
	init_mlx(game);
	return (0);
}
