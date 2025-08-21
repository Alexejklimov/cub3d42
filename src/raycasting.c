
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:11:39 by nmagomad          #+#    #+#             */
/*   Updated: 2025/08/21 17:50:14 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	print_map(t_game *game);
void	render(t_game *game, int x, t_raycast ray);
void	prepare_wall_slice(t_game *game, t_raycast ray, int x);

void	init_raycast(t_game *game, t_raycast *ray, int x)
{

	(*ray).pos_x = game->player.x;
    (*ray).pos_y = game->player.y;
    (*ray).dirX = game->player.dx;
    (*ray).dirY = game->player.dy;
    (*ray).planeX = game->player.plane_x;
    (*ray).planeY = game->player.plane_y;
	(*ray).camera_x = 2 * x / (double)WIDTH - 1;
	(*ray).rayDirX = (*ray).dirX + (*ray).planeX * (*ray).camera_x;
	(*ray).rayDirY = (*ray).dirY + (*ray).planeY * (*ray).camera_x;
	// Текущая позиция на карте
	(*ray).mapX = (int)(*ray).pos_x;
	(*ray).mapY = (int)(*ray).pos_y;
	
}

void	calc_perpwall_wallsize(t_raycast *ray)
{
	// Вычисляем перпендикулярное расстояние до стены (избегаем fish-eye эффекта)
	if ((*ray).side == 0)
		(*ray).perpWallDist = ((*ray).sideDistX - (*ray).deltaDistX);
	else
		(*ray).perpWallDist = ((*ray).sideDistY - (*ray).deltaDistY);
	
	// Вычисляем высоту стены на экране
	(*ray).wall_height = (int)(HEIGHT / (*ray).perpWallDist);
	
	// Определяем начало и конец стены на экране
	(*ray).wall_start = (HEIGHT - (*ray).wall_height) / 2;
	if ((*ray).wall_start < 0)
	{
		// printf("wall_start: %d, perpWall: %f", (*ray).wall_start, (*ray).perpWallDist);// DEBUG LINE
		(*ray).wall_start = 0;
	}
	(*ray).wall_end = (*ray).wall_start + (*ray).wall_height;
	if ((*ray).wall_end >= HEIGHT)
	{
		// printf("wall end: %d\n", (*ray).wall_end);// DEBUG LINE
		(*ray).wall_end = HEIGHT - 1;
	}
	if ((*ray).wall_end < 0)//
		(*ray).wall_end = 0;
}

void	calc_delta_dist(t_raycast *ray)
{
	if ((*ray).rayDirX == 0)
		(*ray).deltaDistX = 1e30;
	else
		(*ray).deltaDistX = fabs(1 / (*ray).rayDirX);
		
	if ((*ray).rayDirY == 0)
		(*ray).deltaDistY = 1e30;
	else
		(*ray).deltaDistY = fabs(1 / (*ray).rayDirY);

	
}

void	calc_side_dist(t_raycast *ray)
{
	if ((*ray).rayDirX < 0)
	{
		(*ray).stepX = -1;
		(*ray).sideDistX = ((*ray).pos_x - (*ray).mapX) * (*ray).deltaDistX;
	}
	else
	{
		(*ray).stepX = 1;
		(*ray).sideDistX = ((*ray).mapX + 1.0 - (*ray).pos_x) * (*ray).deltaDistX;
	}
	
	if ((*ray).rayDirY < 0)
	{
		(*ray).stepY = -1;
		(*ray).sideDistY = ((*ray).pos_y - (*ray).mapY) * (*ray).deltaDistY;
	}
	else
	{
		(*ray).stepY = 1;
		(*ray).sideDistY = ((*ray).mapY + 1.0 - (*ray).pos_y) * (*ray).deltaDistY;
	}
	
}

void	run_dda(t_game *game, t_raycast *ray)
{

	while (1)
	{
		// Переходим к следующему пересечению сетки
		if ((*ray).sideDistX < (*ray).sideDistY)
		{
			(*ray).sideDistX += (*ray).deltaDistX;
			(*ray).mapX += (*ray).stepX;
			(*ray).side = 0;
		}
		else
		{
			(*ray).sideDistY += (*ray).deltaDistY;
			(*ray).mapY += (*ray).stepY;
			(*ray).side = 1; // попадание по горизонтальной стороне
		}
		// Проверяем, попали ли мы в стену
		/* if ((*ray).mapX <= 0 &&
			(*ray).mapX > game->map_width &&
			(*ray).mapY <= 0 &&
			(*ray).mapY > game->map_height && */
		if (game->map[(*ray).mapX][(*ray).mapY] > 0)
			break;
	}
}

// Основная функция raycasting
void raycast(t_game *game)
{
    int x = 0;
	t_raycast	ray;

    // Проходим по каждому столбцу экрана
    while (x < WIDTH)
    {
		// Инициализация позиции и направления игрока
		init_raycast(game, &ray, x);
        
        // Вычисляем дельта расстояния (расстояние между пересечениями сетки)
		calc_delta_dist(&ray);
        
        // Определяем направление шага и начальное расстояние до стороны
		calc_side_dist(&ray);

        // Выполняем DDA (Digital Differential Analyzer)
		run_dda(game, &ray);
		calc_perpwall_wallsize(&ray);
		// printf("%f, wall_height: %d; wall_start: %d; wall_end: %d\n", perpWallDist, wall_height, wall_start, wall_end);
		
		render(game, x, ray);
        x++;
    }
	
}
