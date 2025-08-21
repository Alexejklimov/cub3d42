/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:58:44 by nmagomad          #+#    #+#             */
/*   Updated: 2025/08/21 20:02:25 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


// Функция для установки пикселя в изображение (MLX42 использует RGBA)
void put_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
    if (x >= 0 && x < (int)image->width && y >= 0 && y < (int)image->height)
	{
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

/* void	prepare_wall_slice(t_game *game, t_raycast ray, int x)
{
	t_tex_info	d;
	
	if (ray.side == 0)
		d.wall_x = game->player.y + ray.perpWallDist * ray.rayDirY;
	else
		d.wall_x = game->player.x + ray.perpWallDist * ray.rayDirX;
	d.wall_x = floor(d.wall_x);
	
	d.tex_x = (int)(d.wall_x * (double)game->wall_image->width);
	if ((ray.side == 0 && ray.rayDirX > 0) || (ray.side == 1 && ray.rayDirY < 0))
			d.tex_x = game->wall_image->width - d.tex_x -1;
	d.brightness_factor = 1.0 / (1 + ray.perpWallDist * 0.1);
	if (d.brightness_factor > 1.0)
		d.brightness_factor = 1.0;
	if (d.brightness_factor < 0.2)
		d.brightness_factor = 0.2;
	if (ray.side == 1) 
		d.brightness_factor *= 0.8;
	d.step = 1.0 * (double)game->wall_image->height / ray.wall_height;
	d. = (ray.wall_start - HEIGHT / 2 + ray.wall_height / 2) * step;


} */


void	render(t_game *game, int x, t_raycast ray)
{
	int		y;
	double	wallX;
	int		texX;
	int		texY;
	if (ray.side == 0)
		wallX = game->player.y + ray.perpWallDist * ray.rayDirY;
	else
		wallX = game->player.x + ray.perpWallDist * ray.rayDirX;
	wallX -= floor(wallX);
	
	texX = (int)(wallX * (double)game->wall_image->width);
	if ((ray.side == 0 && ray.rayDirX > 0) || (ray.side == 1 && ray.rayDirY < 0))
			texX = game->wall_image->width - texX -1;
	double brightness_factor = 1.0 / (1 + ray.perpWallDist * 0.1);
	if (brightness_factor > 1.0) brightness_factor = 1.0;
	if (brightness_factor < 0.2) brightness_factor = 0.2;
	
	// Затемняем горизонтальные стены
	if (ray.side == 1) 
		brightness_factor *= 0.8;
	double step = 1.0 * (double)game->wall_image->height / ray.wall_height;
	double texPos = (ray.wall_start - HEIGHT / 2 + ray.wall_height / 2) * step;
	// double texPos = 0;
	// printf("wall strt:%d, %d, %d, %f\n", ray.wall_start, wall_height, ray.wall_end, ray.perpWallDist);


	y = 0;
	while (y < HEIGHT)
	{
		if (y < ray.wall_start)
		{
			// Потолок (небо)
			put_pixel(game->image, x, y, create_color(135, 206, 235, 255)); // светло-голубой
		}
		else if (y >= ray.wall_start && y <= ray.wall_end) // Исправлено: y <= wall_end
		{
			// texY = (int)texPos % (game->wall_image->height);
			texY = (int)texPos & (game->wall_image->height - 1);
			if (texY < 0)
				texY += game->wall_image->height;
			texPos += step;

			// if (!game->DEBUG_FLAG)
				// printf("wallX:%f; texX:%d, texY:%d, wall_height:%d, \n", wallX, texX, texY, ray.wall_height);
			
			uint32_t	tex_color = get_texture_color(game->wall_image, texX, texY);
			
			int r = (tex_color >> 16) & 0xFF;
			int g = (tex_color >> 8) & 0xFF;
			int b = (tex_color) & 0xFF;
			
						
			// Применяем затемнение к цветам текстуры
			r = (int)(r * brightness_factor);
			g = (int)(g * brightness_factor);
			b = (int)(b * brightness_factor);
			
			// Ограничиваем значения
			if (r > 255) r = 255;
			if (g > 255) g = 255;
			if (b > 255) b = 255;

			put_pixel(game->image, x, y, create_color(r, g, b, 255));
		}
		else
		{
			// Пол
			put_pixel(game->image, x, y, create_color(34, 139, 34, 255)); // зеленый
		}
		y++;
	}
	game->DEBUG_FLAG = 1;

}
