/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:07:08 by oklimov           #+#    #+#             */
/*   Updated: 2025/07/15 16:54:24 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



void	game_loop(void *param);
int		init(t_game *game);
void	raycast(t_game *game);
void	handle_movement(t_game *game);
double	ft_get_time();


void	print_map(t_game *game)
{
	size_t	i = 0, j = 0;

	size_t	rows = game->map_info->x;
	size_t	cols = game->map_info->y;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			printf("%d", game->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	ft_check_arg(char *mapname, char *ber)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(mapname) - 4;
	while (mapname[j] != '\0' && ber[i] != '\0' && mapname[j] == ber[i])
	{
		i++;
		j++;
	}
	return (mapname[j] - ber[i]);
}
////////////////////////////

void	check_struct(t_map_info *map)
{
	int	i;

	printf("x = %zu y = %zu\n", map->x, map->y);
	printf("start pos %d, %d\n", map->start_pos[0], map->start_pos[1]);
	printf("start orient - %c\n", map->start_orient);
	printf("floor - %d %d %d\n", map->floor_rgb[0],
		map->floor_rgb[1], map->floor_rgb[2]);
	printf("ceil - %d %d %d\n", map->ceil_rgb[0],
		map->ceil_rgb[1], map->ceil_rgb[2]);
	printf("texture N - %s\n", map->texture[0]);
	printf("texture S - %s\n", map->texture[1]);
	printf("texture W - %s\n", map->texture[2]);
	printf("texture E - %s\n", map->texture[3]);
	i = 0;
	while (map->map[i])
	{
		printf("%s\n", map->map[i]);
		i++;
	}
}
//////////////////// service function to verify struct t_map_info

int	main(int ac, char **av)
{
	t_map_info	*map;
	t_game		*game;

	map = ft_calloc(sizeof(t_map_info), 1);
	game = ft_calloc(sizeof(t_game), 1);
	if (ac != 2 || ft_check_arg(av[1], ".cub") != 0)
		return (ft_printf("Error\n Map path/name isn`t valid\n"));
	parse_map(av[1], map);
	// check_struct(map);
	/* game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win_mlx = mlx_new_window(game->mlx, (map->x) * PXL,
			(map->y) * PXL, "CUB3D");
	if (!game->win_mlx)
		return (free(game->mlx), 1); */
	



	/********************************************************************** */
	game->map_info = map;
	if (init(game) != 0)
	{
		printf("Error init game\n");
		return (EXIT_FAILURE);
	}
		
	game->mlx = mlx_init(WIDTH, HEIGHT, "Simple Raycaster - MLX42", false);
    if (!game->mlx)
	{
        printf("Ошибка инициализации MLX42\n");
        return (EXIT_FAILURE);
    }
    
    // Создание изображения для рендеринга
    game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->image)
	{
        printf("Ошибка создания изображения\n");
        mlx_terminate(game->mlx);
        return (EXIT_FAILURE);
    }
    
    // Добавляем изображение в окно
    if (mlx_image_to_window(game->mlx, game->image, 0, 0) < 0)
	{
        printf("Ошибка добавления изображения в окно\n");
        mlx_terminate(game->mlx);
        return (EXIT_FAILURE);
    }
	
	// init texture 
	xpm_t	*wall_texture = mlx_load_xpm42(game->map_info->texture[0]);
	if (!wall_texture)
	{
        printf("Error: load XMP42 file\n");
        mlx_terminate(game->mlx);
        return (EXIT_FAILURE);
	}
	game->wall_image = mlx_texture_to_image(game->mlx, &wall_texture->texture);

	mlx_loop_hook(game->mlx, game_loop, game);
    
    mlx_loop(game->mlx);
    
    mlx_terminate(game->mlx);


	return (0);
}



void game_loop(void *param)
{
    t_game *game = (t_game *)param;
	double	time;
	double	frame_time;
	

	time = ft_get_time();
	if (game->first_frame)
	{
		game->oldtime = time;
		frame_time = 0.016;
		game->first_frame = 0;
		
	}
	else
	{
		frame_time = (time - game->oldtime) / 1000.0;
	}
	
	// printf("Time: %f ms, FrameTime: %f s\n", time, frame_time);
    // if (frame_time > 0)
        // printf("FPS: %.2f\n", 1.0 / frame_time);
    
    game->oldtime = time;
	game->move_speed = frame_time * 5.0;
	game->move_rotate = frame_time * 3.0;
	// printf("move speed: %f, rotate speed: %f\n", game->move_speed, game->move_rotate);
	
    handle_movement(game);
    raycast(game);
}
