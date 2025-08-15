/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:56:02 by oklimov           #+#    #+#             */
/*   Updated: 2025/08/08 17:04:40 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	parse_map(char *file, t_map_info *map_info)
{
	char	**buffer_map;

	buffer_map = separate_map(read_map(file), map_info);
	check_map_is_valid(buffer_map, map_info);
	fill_start_pos_orient(map_info);
}

static int	is_valid_surrounding(char **map, size_t x, size_t y)
{
	if (x == 0 || map[x + 1] == NULL || y == 0
		|| y >= ft_strlen(map[x - 1]) || y >= ft_strlen(map[x + 1])
		|| map[x][y + 1] == '\0')
		return (0);
	if (ft_strchr("\n ", (int)map[x][y + 1])
		|| ft_strchr("\n ", (int)map[x][y - 1])
		|| ft_strchr("\n ", (int)map[x + 1][y])
		|| ft_strchr("\n ", (int)map[x - 1][y]))
		return (0);
	return (1);
}

int	check_walls_is_valid(char **map)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (map[x] != NULL)
	{
		y = 0;
		while (map[x][y] != '\0')
		{
			if (ft_strchr("NSEW0", (int)map[x][y]))
				if (!is_valid_surrounding(map, x, y))
					return (0);
			y++;
		}
		x++;
	}
	return (1);
}

int	is_symbols_valid_only(char **map)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\n' && map[i][j] != '\0')
		{
			if (!ft_strchr("NSEW 10", (int)map[i][j]))
				return (printf("Error\ninvalid symbol in map"), 0);
			if (ft_strchr("NSEW", map[i][j]))
				flag++;
			j++;
		}
		i++;
	}
	if (flag != 1)
		return (perror("Error\nto many start positions"), 0);
	return (1);
}

void	check_map_is_valid(char **map, t_map_info *map_info)
{
	if (!is_symbols_valid_only(map))
	{
		free_map(map);
	}
	if (!verify_texture(map_info))
		ft_printf("Error\nTexture data not valid\n");
	if (!check_walls_is_valid(map))
		ft_printf("Error\nWalls is invalid\n");
	make_map_rectangular(map, map_info);
	free_map(map);
}
/// add exits if error
