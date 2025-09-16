/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:45:50 by nmagomad          #+#    #+#             */
/*   Updated: 2025/09/16 17:47:02 by nmagomad         ###   ########.fr       */
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
