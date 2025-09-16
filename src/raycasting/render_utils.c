/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:45:50 by nmagomad          #+#    #+#             */
/*   Updated: 2025/09/15 16:27:43 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	if (x >= 0 && x < (int)image->width && y >= 0 && y < (int)image->height)
	{
		mlx_put_pixel(image, x, y, color);
	}
}

uint32_t	create_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

double	calculate_wall_brightness(t_raycast *ray)
{
	double	brightness;

	brightness = 1.0 / (1 + ray->perpwalldist * 0.1);
	if (brightness > 1.0)
		brightness = 1.0;
	if (brightness < 0.2)
		brightness = 0.2;
	if (ray->side == 1)
		brightness *= 0.8;
	return (brightness);
}

uint32_t	apply_brightness(uint32_t color, double brightness, int alpha)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = (color) & 0xFF;
	r = (int)(r * brightness);
	g = (int)(g * brightness);
	b = (int)(b * brightness);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (create_color(r, g, b, alpha));
}

uint32_t	get_texture_color(mlx_image_t *texture, int tex_x, int tex_y)
{
	uint8_t	*pixel;

	if (tex_x < 0 || tex_x >= (int)texture->width
		|| tex_y < 0 || tex_y >= (int)texture->height)
		return (0xFF000000);
	pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
	return ((pixel[3] << 24) | (pixel[0] << 16) | (pixel[1] << 8) | pixel[2]);
}

mlx_image_t	*get_curr_texture(t_game *game, t_raycast *ray)
{
	mlx_image_t	*texture;

	if (ray->side == 0)
	{
		if (ray->raydir_x > 0)
			texture = game->walls[EAST];
		else
			texture = game->walls[WEST];
	}
	else
	{
		if (ray->raydir_y > 0)
			texture = game->walls[SOUTH];
		else
			texture = game->walls[NORD];
	}
	return (texture);
}
