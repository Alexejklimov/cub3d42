/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:07:08 by oklimov           #+#    #+#             */
/*   Updated: 2025/07/15 16:54:24 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_arg(char *mapname, char *ber)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(mapname) - 4;
	while (mapname[j] != '\0' && ber[i] != '\0' && mapname[j] == ber[i])
	{
		i++;
		j++;
	}
	return (mapname[j] - ber[i]);
}
////////////////////////////

void	check_struct(t_map_info *map)
{
	int	i;

	printf("x = %zu y = %zu\n", map->x, map->y);
	printf("start pos %d, %d\n", map->start_pos[0], map->start_pos[1]);
	printf("start orient - %c\n", map->start_orient);
	printf("floor - %d %d %d\n", map->floor_rgb[0],
		map->floor_rgb[1], map->floor_rgb[2]);
	printf("ceil - %d %d %d\n", map->ceil_rgb[0],
		map->ceil_rgb[1], map->ceil_rgb[2]);
	printf("texture N - %s\n", map->texture[0]);
	printf("texture S - %s\n", map->texture[1]);
	printf("texture W - %s\n", map->texture[2]);
	printf("texture E - %s\n", map->texture[3]);
	i = 0;
	while (map->map[i])
	{
		printf("%s\n", map->map[i]);
		i++;
	}
}
//////////////////// service function to verify struct t_map_info

int	main(int ac, char **av)
{
	t_map_info	*map;
	t_game		*game;

	map = ft_calloc(sizeof(t_map_info), 1);
	game = ft_calloc(sizeof(t_game), 1);
	if (ac != 2 || ft_check_arg(av[1], ".cub") != 0)
		return (ft_printf("Error\n Map path/name isn`t valid\n"));
	parse_map(av[1], map);
	//check_struct(map);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win_mlx = mlx_new_window(game->mlx, (map->x) * PXL,
			(map->y) * PXL, "CUB3D");
	if (!game->win_mlx)
		return (free(game->mlx), 1);
	return (0);
}
