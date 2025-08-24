/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:35:04 by nmagomad          #+#    #+#             */
/*   Updated: 2025/08/24 18:57:14 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	int	allocate_map(t_game *game)
{
	size_t	i;

	if (!game)
		return (-1);
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
		free(game->map);
		return (-1);
	}
	i = 1;
	while (i < game->map_info->x)
	{
		game->map[i] = game->map[0] + i * game->map_info->y;
		i++;
	}
	return (0);
}

static void	convet_map_to_int(t_game *game)
{
	size_t	i;
	size_t	j;

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
}
/*
 * | Направление | dirX | dirY | planeX | planeY |
 * | ----------- | ---- | ---- | ------ | ------ |
 * | **N**       | 0    | -1   | 0.66   | 0      |
 * | **S**       | 0    | 1    | -0.66  | 0      |
 * | **E**       | 1    | 0    | 0      | 0.66   |
 * | **W**       | -1   | 0    | 0      | -0.66  |
*/
static	void	init_direction(t_game *game)
{
	char		dir;
	t_vector	direction[256];
	
	if (!game || !game->map_info)
		panic("pointer `game or man_info` is NULL");
	ft_memset(&direction, 0, sizeof(direction));
	dir = game->map_info->start_orient;
	direction['N'] = (t_vector){0, -1, 0.66, 0};
	direction['S'] = (t_vector){0, 1, -0.66, 0};
	direction['E'] = (t_vector){1, 0, 0, 0.66};
	direction['W'] = (t_vector){-1, 0, 0, 0.66};
	printf("%f, %f, %f, %f\n", game->player.dx, game->player.dy, game->player.plane_x, game->player.plane_y);
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
	printf("%f, %f, %f, %f\n", game->player.dx, game->player.dy, game->player.plane_x, game->player.plane_y);
}

static void	init_ceiling_floor_colort(t_game *game)
{
	int	r;
	int	g;
	int	b;

	if (!game || game->map_info)
		panic("pointer `game or man_info` is NULL");
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

	printf("%d, %d\n", game->map_info->start_pos[0], game->map_info->start_pos[1]);
	if (game->map_info->start_pos[0])
		game->player.x = game->map_info->start_pos[0];
	game->player.y = game->map_info->start_pos[1];
	// game->player.dx = -1;
	// game->player.dy = 0;
	// game->player.plane_x = 0;
	// game->player.plane_y = 0.66;
	init_direction(game);
	init_ceiling_floor_color(game);
	game->oldtime = 0;
	game->map_width = game->map_info->y;
	game->map_height = game->map_info->x;
	
	if (allocate_map(game) != 0)
		return (-1);
	convet_map_to_int(game);
	return (0);
}
