/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:54:23 by nmagomad          #+#    #+#             */
/*   Updated: 2025/09/16 17:05:21 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_texture(t_game *game)
{
	xpm_t		*xpm;
	char		*path;
	int			i;

	i = 0;
	while (i < 4)
	{
		path = game->map_info->texture[i];
		xpm = mlx_load_xpm42(path);
		if (!xpm)
		{
			ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
			return (-1);
		}
		game->walls[i] = mlx_texture_to_image(game->mlx, &xpm->texture);
		if (!game->walls[i])
		{
			ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
			return (-1);
		}
		mlx_delete_xpm42(xpm);
		i++;
	}
	return (0);
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", false);
	if (!game->mlx)
		errexit(game, "Error: init MLX");
	game->image = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->image)
		errexit(game, "Error: creat image");
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) < 0)
		errexit(game, "Error: creat image");
	if (load_texture(game) != 0)
		errexit(game, 0);
}
