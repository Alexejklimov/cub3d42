/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:12:25 by nmagomad          #+#    #+#             */
/*   Updated: 2025/09/16 18:17:12 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_map_info(t_map_info *map_info)
{
	int	i;

	if (map_info->map)
		free_map(map_info->map);
	i = 0;
	while (i < 4)
	{
		if (map_info->texture[i])
			free(map_info->texture[i]);
		i++;
	}
	free(map_info);
	exit (1);
}

void	clean_map(t_game *game)
{
	if (game->map[0])
		free(game->map[0]);
	if (game->map)
		free(game->map);
	game->map[0] = NULL;
	game->map = NULL;
	game = NULL;
}

void	free_map(char **map)
{
	int	y;

	if (map == NULL)
		return ;
	y = 0;
	while (map[y] != NULL)
	{
		free(map[y]);
		y++;
	}
	free(map);
}

void	cleanup(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->walls[i])
			mlx_delete_image(game->mlx, game->walls[i]);
		i++;
	}
	if (game->image)
		mlx_delete_image(game->mlx, game->image);
	if (game->mlx)
		mlx_terminate(game->mlx);
	if (game->map_info)
		clean_map_info(game->map_info);
	if (game->map)
		clean_map(game);
	if (game)
		free(game);
}
