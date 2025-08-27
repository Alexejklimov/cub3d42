/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:58:44 by nmagomad          #+#    #+#             */
/*   Updated: 2025/08/25 19:03:52 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint32_t	_get_texture_color(t_game *game, t_raycast *ray,int tex_x, int tex_y);

/**
 * @brief Prepares wall rendering parameters for a ray in a raycasting engine.
 *
 * This function calculates the screen-space height, start and end positions
 * of the wall slice, the exact texture coordinate, and brightness for shading
 * based on the ray's distance and orientation.
 *
 * @param game Pointer to the game structure containing texture and screen info.
 * @param ray Pointer to the ray structure with raycasting results.
 * @param wall Pointer to the wall structure where rendering parameters will be 
 *        stored.
 *
 * @details
 * - wall_height is calculated from the perpendicular distance to the wall.
 * - wall_start and wall_end define the vertical slice of the wall to draw.
 * - wall_x is the precise horizontal position on the wall where the ray hits.
 * - tex_x is the corresponding x-coordinate on the wall texture.
 * - brightness is calculated based on distance and side, 
 *   clamped between 0.2 and 1.0.
 */
void	prepare_wall_render(t_game *game, t_raycast *ray, t_wall *wall)
{
	ray->wall_height = (int)(SCREEN_HEIGHT / ray->perpwalldist);
	ray->wall_start = (SCREEN_HEIGHT - ray->wall_height) / 2;
	if (ray->wall_start < 0)
		ray->wall_start = 0;
	ray->wall_end = ray->wall_start + ray->wall_height;
	if (ray->wall_end >= SCREEN_HEIGHT)
		ray->wall_end = SCREEN_HEIGHT - 1;
	if (ray->wall_end < 0)
		ray->wall_end = 0;
	if (ray->side == 0)
		wall->wall_x = ray->pos_y + ray->perpwalldist * ray->raydir_y;
	else
		wall->wall_x = ray->pos_x + ray->perpwalldist * ray->raydir_x;
	wall->wall_x -= floor(wall->wall_x);
	wall->tex_x = (int)(wall->wall_x * (double)game->wall_image->width);
	if ((ray->side == 0 && ray->raydir_x > 0)
		|| (ray->side == 1 && ray->raydir_y < 0))
		wall->tex_x = game->wall_image->width - wall->tex_x - 1;
	wall->brightness = 1.0 / (1 + ray->perpwalldist * 0.1);
	if (wall->brightness > 1.0)
		wall->brightness = 1.0;
	if (wall->brightness < 0.2)
		wall->brightness = 0.2;
	if (ray->side == 1)
		wall->brightness *= 0.8;
}

void	render(t_game *game, int x, t_raycast *ray, t_wall *wall)
{
	int			y;
	uint32_t	tex_color;
	double		step;
	double		tex_pos;

	step = 1.0 * (double)game->wall_image->height / ray->wall_height;
	tex_pos = (ray->wall_start - SCREEN_HEIGHT / 2 + ray->wall_height / 2) * step;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		if (y < ray->wall_start)
			// put_pixel(game->image, x, y, create_color(135, 206, 235, 255)); //Потолок (небо); светло-голубой
			put_pixel(game->image, x, y, game->ceil_color);
		else if (y >= ray->wall_start && y <= ray->wall_end) // Исправлено: y <= wall_end
		{
			// wall->tex_y = (int)texPos % (game->wall_image->height);
			wall->tex_y = (int)tex_pos & (game->wall_image->height - 1);
			if (wall->tex_y < 0)
				wall->tex_y += game->wall_image->height;
			tex_pos += step;
			// tex_color = get_texture_color(game->wall_image, wall->tex_x, wall->tex_y);
			tex_color = _get_texture_color(game, ray, wall->tex_x, wall->tex_y);
			tex_color = apply_brightness(tex_color, wall->brightness, 255);
			put_pixel(game->image, x, y, tex_color);
			// put_pixel(game->image, x, y, create_color(r, g, b, 255));
		}
		else
			// put_pixel(game->image, x, y, create_color(34, 139, 34, 255)); // Пол; зеленый
			put_pixel(game->image, x, y, game->floor_color);
		y++;
	}
}
