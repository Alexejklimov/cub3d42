/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:58:44 by nmagomad          #+#    #+#             */
/*   Updated: 2025/09/15 15:00:05 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*get_curr_texture(t_game *game, t_raycast *ray);
void		compute_wall_hit_position(t_raycast *ray, t_wall *wall);
int			step_texture_y(t_wall *wall);
double		calculate_wall_brightness(t_raycast *ray);

void	calculate_wall_geometry(t_raycast *ray)
{
	ray->wall.height = (int)(SCREEN_HEIGHT / ray->perpwalldist);
	ray->wall.start = (SCREEN_HEIGHT - ray->wall.height) / 2;
	if (ray->wall.start < 0)
		ray->wall.start = 0;
	ray->wall.end = ray->wall.start + ray->wall.height;
	if (ray->wall.end >= SCREEN_HEIGHT)
		ray->wall.end = SCREEN_HEIGHT - 1;
	if (ray->wall.end < 0)
		ray->wall.end = 0;
}

void	compute_wall_hit_position(t_raycast *ray, t_wall *wall)
{
	if (ray->side == 0)
		wall->wall_x = ray->pos_y + ray->perpwalldist * ray->raydir_y;
	else
		wall->wall_x = ray->pos_x + ray->perpwalldist * ray->raydir_x;
	wall->wall_x -= floor(wall->wall_x);
}

void	prepare_wall_render(t_game *game, t_raycast *ray, t_wall *wall)
{
	calculate_wall_geometry(ray);
	compute_wall_hit_position(ray, wall);
	wall->brightness = calculate_wall_brightness(ray);
	wall->image = get_curr_texture(game, ray);
	wall->tex_x = (int)(wall->wall_x * (double)wall->image->width);
	if ((ray->side == 0 && ray->raydir_x > 0)
		|| (ray->side == 1 && ray->raydir_y < 0))
		wall->tex_x = wall->image->width - wall->tex_x - 1;
	wall->tex_step = 1.0 * (double)wall->image->height / ray->wall.height;
	wall->tex_pos = (ray->wall.start - SCREEN_HEIGHT / 2 + ray->wall.height / 2)
		* wall->tex_step;
}

int	step_texture_y(t_wall *wall)
{
	wall->tex_y = (int)wall->tex_pos & (wall->image->height - 1);
	if (wall->tex_y < 0)
		wall->tex_y += wall->image->height;
	wall->tex_pos += wall->tex_step;
	return (wall->tex_y);
}

void	render(t_game *game, int x, t_raycast *ray, t_wall *wall)
{
	int			y;
	uint32_t	tex_color;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		if (y < ray->wall.start)
			put_pixel(game->image, x, y, game->ceil_color);
		else if (y >= ray->wall.start && y <= ray->wall.end)
		{
			step_texture_y(wall);
			tex_color = get_texture_color(wall->image, wall->tex_x, wall->tex_y);
			tex_color = apply_brightness(tex_color, wall->brightness, 255);
			put_pixel(game->image, x, y, tex_color);
		}
		else
			put_pixel(game->image, x, y, game->floor_color);
		y++;
	}
}
