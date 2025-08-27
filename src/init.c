/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:35:04 by nmagomad          #+#    #+#             */
/*   Updated: 2025/08/27 15:12:59 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	debug_print(t_game *game);
void	errexit(t_game *game, char *msg);

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
		panic("Error: Pointer `game or man_info` is NULL");
	ft_memset(&direction, 0, sizeof(direction));
	dir = game->map_info->start_orient;
	// direction['N'] = (t_vector){0, -1, 0.66, 0}; // old
	direction['N'] = (t_vector){-1, 0, 0, 0.66};
	// direction['S'] = (t_vector){0, 1, -0.66, 0}; // old
	direction['S'] = (t_vector){1, 0, 0, 0.66};
	// direction['E'] = (t_vector){1, 0, 0, 0.66}; // old
	direction['E'] = (t_vector){0, 1, -0.66, 0};
	// direction['W'] = (t_vector){-1, 0, 0, 0.66}; //old
	direction['W'] = (t_vector){0, -1, 0.66, 0};
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

int	load_texture(t_game *game)
{
	xpm_t		*xpm;
	char		*path;
	int			i;

	i = 0;
	while (i < 4)
	{
		path = game->map_info->texture[i];
		xpm = mlx_load_xpm42(path);
		if (!xpm)
		{
			ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
			return (-1);
		}
		game->walls[i] = mlx_texture_to_image(game->mlx, &xpm->texture);
		if (!game->walls[i])
		{
			ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
			return (-1);
		}
		mlx_delete_xpm42(xpm);
		i++;
	}
	return (0);
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", false);
	if (!game->mlx)
		errexit(game, "Error: init MLX");
	game->image = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->image)
		errexit(game, "Error: creat image");
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) < 0)
		errexit(game, "Error: creat image");
	if (load_texture(game) != 0)
		errexit(game, 0);
}

int	init(t_game *game)
{
	if (game->map_info->start_pos[0])
		game->player.x = game->map_info->start_pos[0] + 0.5;
	if (game->map_info->start_pos[1])
	game->player.y = game->map_info->start_pos[1] + 0.5;
	init_direction(game);
	init_ceiling_floor_color(game);
	game->oldtime = 0;
	game->map_width = game->map_info->y;
	game->map_height = game->map_info->x;
	if (allocate_map(game) != 0)
		return (-1);
	convet_map_to_int(game);
	init_mlx(game);
	return (0);
}
