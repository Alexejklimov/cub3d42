/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:39:13 by nmagomad          #+#    #+#             */
/*   Updated: 2025/08/24 15:59:19 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_map(t_game *game);
void	render(t_game *game, int x, t_raycast *ray, t_wall *wall);
void	prepare_wall_render(t_game *game, t_raycast *ray, t_wall *wall);

static void	init_raycast(t_game *game, t_raycast *ray, int x)
{
	if (!game || !ray)
		panic("Error: init_raycast get NULL pointer");
	ray->pos_x = game->player.x;
    ray->pos_y = game->player.y;
    ray->dir_x = game->player.dx;
    ray->dir_y = game->player.dy;
    ray->plane_x = game->player.plane_x;
    ray->plane_y = game->player.plane_y;
	ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->raydir_x = ray->dir_x + ray->plane_x * ray->camera_x;
	ray->raydir_y = ray->dir_y + ray->plane_y * ray->camera_x;
	// Текущая позиция на карте
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	if (ray->raydir_x == 0)
		ray->deltadist_x = 1e30;
	else
		ray->deltadist_x = fabs(1 / ray->raydir_x);
	if (ray->raydir_y == 0)
		ray->deltadist_y = 1e30;
	else
		ray->deltadist_y = fabs(1 / ray->raydir_y);
}

static void	calc_perpwalldist(t_raycast *ray)
{
	if (ray->side == 0)
		ray->perpwalldist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->perpwalldist = (ray->sidedist_y - ray->deltadist_y);
}

static void	calc_side_dist(t_raycast *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (ray->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->deltadist_x;
	}
	
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (ray->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->deltadist_y;
	}
	
}

static void	run_dda(t_game *game, t_raycast *ray)
{

	while (1)
	{
		// Переходим к следующему пересечению сетки
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1; // попадание по горизонтальной стороне
		}
		// Проверяем, попали ли мы в стену
		/* if (ray->mapX <= 0 &&
			ray->mapX > game->map_width &&
			ray->mapY <= 0 &&
			ray->mapY > game->map_height && */
		if (game->map[ray->map_x][ray->map_y] > 0)
			break ;
	}
}

// Основная функция raycasting
void raycast(t_game *game)
{
    int 		x;
	t_raycast	ray;
	t_wall		wall;

    // Проходим по каждому столбцу экрана
	x = 0;
    while (x < SCREEN_WIDTH)
    {
		// Инициализация позиции и направления игрока
		init_raycast(game, &ray, x);
        
        // Вычисляем дельта расстояния (расстояние между пересечениями сетки)
        
        // Определяем направление шага и начальное расстояние до стороны
		calc_side_dist(&ray);

        // Выполняем DDA (Digital Differential Analyzer)
		run_dda(game, &ray);
		calc_perpwalldist(&ray);
		// printf("%f, wall_height: %d; wall_start: %d; wall_end: %d\n", perpWallDist, wall_height, wall_start, wall_end);
		// вычисляем высоту стены, начал и конез отрисовки стены, и другие данные для отрисовки
		prepare_wall_render(game, &ray, &wall);
		render(game, x, &ray, &wall);
        x++;
    }
	
}
