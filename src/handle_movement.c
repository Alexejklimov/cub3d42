/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:43:42 by nmagomad          #+#    #+#             */
/*   Updated: 2025/08/18 18:32:08 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move(t_game *game, double axis_x, double axis_y, int sign)
{
	double	new_x;
	double	new_y;
	size_t	height;
	size_t	width;
	
	height = game->map_info->y;
	width = game->map_info->x;

	if (sign == 1 || sign == -1)
	{
		new_x = game->player.x + (sign * axis_x) * game->move_speed;
		new_y = game->player.y + (sign * axis_y) * game->move_speed;
	}
	else
	{
		printf("Error: sing is not correct\n");
		return ;
	}
	// if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height)
	if (new_x >= 0.25 && new_x < width - 0.25 && new_y >= 0.25 && new_y < height - 0.25)
	{
		if (game->map[(int)new_x][(int)game->player.y] == 0)
			game->player.x = new_x;
		if (game->map[(int)game->player.x][(int)new_y] == 0)
                game->player.y = new_y;
	}
}


void	rotate(t_game *game, int sign)
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	rot_speed;
	
	dir_x = game->player.dx;
	dir_y= game->player.dy;
	plane_x = game->player.plane_x;
	plane_y = game->player.plane_y;
	rot_speed = sign * game->move_rotate;

	game->player.dx = dir_x * cos(rot_speed) - dir_y * sin(rot_speed);
	game->player.dy = dir_x * sin(rot_speed) + dir_y * cos(rot_speed);
	game->player.plane_x = plane_x * cos(rot_speed) - plane_y * sin(rot_speed);
	game->player.plane_y = plane_x * sin(rot_speed) + plane_y * cos(rot_speed);
}


void handle_movement(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move(game, game->player.dx, game->player.dy, 1);
    // S - движение назад
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move(game, game->player.dx, game->player.dy, -1);
	// A - движение назад
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move(game, game->player.plane_x, game->player.plane_y, -1);
	// D - движение вперед
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move(game, game->player.plane_x, game->player.plane_y, 1);
    
    // LEFT - поворот влево
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate(game, 1);
    // RIGHT - поворот вправо
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate(game, -1);
    // ESC - выход
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(game->mlx);
}
