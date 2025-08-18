/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:11:39 by nmagomad          #+#    #+#             */
/*   Updated: 2025/08/18 19:51:50 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	print_map(t_game *game);

// Функция для установки пикселя в изображение (MLX42 использует RGBA)
void put_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
    if (x >= 0 && x < (int)image->width && y >= 0 && y < (int)image->height) {
        mlx_put_pixel(image, x, y, color);
    }
}

// Создание цвета в формате RGBA
uint32_t create_color(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	get_texture_color(mlx_image_t *texture, int tex_x, int tex_y)
{
	uint8_t	*pixel;
	if (tex_x < 0 || tex_x >= (int)texture->width || tex_y < 0 || tex_y >= (int)texture->height)
		return (0xFF000000);
	pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
	return ((pixel[3] << 24) | (pixel[0] << 16) | (pixel[1] << 8) | pixel[2]);
}

void	dda_algorithm(t_raycast *raycast, int **world_map, int map_width, int map_height)
{
	t_raycast	r;

	if (!raycast)
		return ;
	r = *raycast;
	while (true)
	{
		if (r.side_dist_x < r.side_dist_y)
		{
			r.side_dist_x += r.delt_dist_x;
			r.map_x += r.step_x;
			r.side = 0;
		}
		else
		{
			r.side_dist_y += r.side_dist_y;
			r.map_y += r.step_y;
			r.side = 1;
		}
		if (r.map_x >= 0 && r.map_x < map_width && r.map_y >= 0 &&
			r.map_y < map_height && world_map[r.map_x][r.map_y] > 0)
			break;
	}
	*raycast = r;
}

void	calc_perp_wall_dist(t_raycast *raycast)
{
	t_raycast	r;
	
	if (!raycast)
		return ;
	r = *raycast;
	if (r.side == 0)
		r.perp_wall_dist = (r.side_dist_x - r.delt_dist_x);
	else
		r.perp_wall_dist = (r.side_dist_y - r.delt_dist_y);
	if (r.perp_wall_dist < 0.25)// testing
		r.perp_wall_dist = 0.25;//
        
	r.wall_height = (int)(HEIGHT / r.perp_wall_dist);
	if (r.wall_height > HEIGHT)//
		r.wall_height = HEIGHT;//
	r.wall_start = (HEIGHT - r.wall_height) / 2;
	if (r.wall_start < 0)
		r.wall_start = 0;
	r.wall_end = r.wall_start + r.wall_height;
	if (r.wall_end >= HEIGHT)
		r.wall_end = HEIGHT - 1;
	if (r.wall_end < 0)//
		r.wall_end = 0;
	*raycast = r;
}

// Основная функция raycasting
void raycast(t_game *game)
{
    int x = 0;
    double posX, posY;
    double dirX, dirY;
    double plane_x, plane_y;
    double cameraX;
    double rayDirX, rayDirY;
    double sideDistX, sideDistY;
    double deltaDistX, deltaDistY;
    double perpWallDist; 
    int stepX, stepY;
    int side;
	int **world_map = game->map;

    
    // Инициализация позиции и направления игрока
    posX = game->player.x;
    posY = game->player.y;
    dirX = game->player.dx;
    dirY = game->player.dy;
    plane_x = game->player.plane_x;
    plane_y = game->player.plane_y;
	int	map_width = game->map_info->y;
	int	map_height = game->map_info->y;

    
    // Проходим по каждому столбцу экрана
    while (x < WIDTH)
    {
        // Вычисляем направление луча для текущего столбца
        cameraX = 2 * x / (double)WIDTH - 1; // координата камеры от -1 до 1
        rayDirX = dirX + plane_x * cameraX;
        rayDirY = dirY + plane_y * cameraX;
        
        // Текущая позиция на карте
        int mapX = (int)posX;
        int mapY = (int)posY;
        
        // Вычисляем дельта расстояния (расстояние между пересечениями сетки)
        if (rayDirX == 0)
            deltaDistX = 1e30;
        else
            deltaDistX = fabs(1 / rayDirX);
            
        if (rayDirY == 0)
            deltaDistY = 1e30;
        else
            deltaDistY = fabs(1 / rayDirY);
        
        // Определяем направление шага и начальное расстояние до стороны
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }
        
        // Выполняем DDA (Digital Differential Analyzer)
        // hit = 0; // Сброс флага попадания для каждого нового луча
        // while (hit == 0)
        while (1)
        {
            // Переходим к следующему пересечению сетки
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0; // попадание по вертикальной стороне
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1; // попадание по горизонтальной стороне
            }
            
            // Проверяем, попали ли мы в стену
            if (mapX >= 0 && mapX < map_width && mapY >= 0 && mapY < map_height && // Добавлена проверка границ
                world_map[mapX][mapY] > 0)
				break;
                // hit = 1;
        }
        
        // Вычисляем перпендикулярное расстояние до стены (избегаем fish-eye эффекта)
        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);
		if (perpWallDist < 0.25)//
			perpWallDist = 0.25;//
        
        // Вычисляем высоту стены на экране
        int wall_height = (int)(HEIGHT / perpWallDist);
		if (wall_height > HEIGHT)//
			wall_height = HEIGHT;//
        
        // Определяем начало и конец стены на экране
        int wall_start = (HEIGHT - wall_height) / 2;
        if (wall_start < 0)
            wall_start = 0;
            
        int wall_end = wall_start + wall_height;
        if (wall_end >= HEIGHT)
            wall_end = HEIGHT - 1;
        if (wall_end < 0)//
			wall_end = 0;
		printf("%f, wall_height: %d; wall_start: %d; wall_end: %d\n", perpWallDist, wall_height, wall_start, wall_end);
        // Рисуем вертикальную линию
        for (int y = 0; y < HEIGHT; y++)
        {
            if (y < wall_start)
            {
                // Потолок (небо)
                put_pixel(game->image, x, y, create_color(135, 206, 235, 255)); // светло-голубой
            }
            else if (y >= wall_start && y <= wall_end) // Исправлено: y <= wall_end
            {
				double	wallX;
				if (side == 0)
					wallX = game->player.y + perpWallDist * rayDirY;
				else
					wallX = game->player.x + perpWallDist * rayDirX;
				wallX -= floor(wallX);
				
				int	texX = (int)(wallX * (double)game->wall_image->width);
				if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
						texX = game->wall_image->width - texX -1;
				int	texY = (int)((double)(y - wall_start ) / (wall_end - wall_start) * game->wall_image->height);
				
				uint32_t	tex_color = get_texture_color(game->wall_image, texX, texY);
				
				
				int r = (tex_color >> 16) & 0xFF;
				int g = (tex_color >> 8) & 0xFF;
				int b = (tex_color) & 0xFF;
				
				double brightness_factor = 1.0 / (1 + perpWallDist * 0.1);
				if (brightness_factor > 1.0) brightness_factor = 1.0;
				if (brightness_factor < 0.2) brightness_factor = 0.2;
				
				// Затемняем горизонтальные стены
				if (side == 1) 
					brightness_factor *= 0.8;
				
				// Применяем затемнение к цветам текстуры
				r = (int)(r * brightness_factor);
				g = (int)(g * brightness_factor);
				b = (int)(b * brightness_factor);
				
				// Ограничиваем значения
				if (r > 255) r = 255;
				if (g > 255) g = 255;
				if (b > 255) b = 255;

			//*************************************************************** */	
			//**** no texture */
            /*     // Стена с эффектом затемнения по расстоянию
                int brightness = (int)(255 / (1 + perpWallDist * 0.1));
                if (brightness > 255) brightness = 255;
                if (brightness < 50) brightness = 50;
                
                // Можно добавить различные цвета для разных сторон стены
                if (side == 1) // горизонтальные стены чуть темнее
                    brightness = brightness * 0.8;
				// no texture
                put_pixel(game->image, x, y, create_color(brightness, brightness, brightness, 255)); */
			//**** no texture */
			//
				// with texture
                put_pixel(game->image, x, y, create_color(r, g, b, 255));
            }
            else
            {
                // Пол
                put_pixel(game->image, x, y, create_color(34, 139, 34, 255)); // зеленый
            }
        }
        x++;
    }
	
}
