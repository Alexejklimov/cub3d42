/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:56:02 by oklimov           #+#    #+#             */
/*   Updated: 2025/10/24 13:27:58 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	parse_map(char *file, t_map_info *map_info)
{
	char	**buffer_map;

	buffer_map = separate_map(read_map(file), map_info);
	if (!buffer_map)
		return (0);
	if (!check_map_is_valid(buffer_map, map_info))
	{
		free_map(buffer_map);
		clean_map_info(map_info);
		return (0);
	}
	fill_start_pos_orient(map_info);
	if (!map_info_fill_checker(map_info))
	{
		free_map(buffer_map);
		clean_map_info(map_info);
		return (0);
	}
	free_map(buffer_map);
	return (1);
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
				return (ft_printf("Error\ninvalid symbol in map\n"), 0);
			if (ft_strchr("NSEW", map[i][j]))
				flag++;
			j++;
		}
		i++;
	}
	if (flag != 1)
		return (ft_printf("Error\nmap file is incorrect\n"), 0);
	return (1);
}

char	**separate_map(char **file, t_map_info *map_info)
{
	int			i;
	int			j;
	int			acc;
	char		**separated_map;

	i = -1;
	while (++i < 3)
	{
		map_info->floor_rgb[i] = -1;
		map_info->ceil_rgb[i] = -1;
	}
	i = parse_texture(file, map_info);
	if (i == 0)
		return (printf("Error\nincorrect file info\n"), free_map(file), NULL);
	acc = i;
	while (file[acc] != NULL)
		acc++;
	separated_map = malloc(sizeof(char *) * acc);
	j = 0;
	while (file[i] && file[i][0] != '\n')
		separated_map[j++] = ft_strdup(file[i++]);
	separated_map[j] = NULL;
	is_end_of_file(map_info, file, separated_map, i);
	return (free_map(file), separated_map);
}
