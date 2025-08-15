/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:05:17 by oklimov           #+#    #+#             */
/*   Updated: 2025/08/08 17:04:23 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	texture_end_fixer(t_map_info *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (map->texture[i][j])
		{
			if (map->texture[i][j] == '\n')
				map->texture[i][j] = '\0';
			j++;
		}
		i++;
	}
}

void	fill_start_pos_orient(t_map_info *map_info)
{
	int	x;
	int	y;

	x = 0;
	while (map_info->map[x])
	{
		y = 0;
		while (map_info->map[x][y])
		{
			if (ft_strchr("NSWE", (int)map_info->map[x][y]))
			{
				map_info->start_orient = map_info->map[x][y];
				map_info->start_pos[0] = x;
				map_info->start_pos[1] = y;
			}
			y++;
		}
		x++;
	}
}

size_t	longest_row(char	**map)
{
	size_t	max;
	size_t	i;

	i = 0;
	max = ft_strlen(map[i]);
	while (map[i])
	{
		if (max < ft_strlen(map[i]))
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

char	*fix_line(char	*str, size_t max_len)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	j = 0;
	line = ft_calloc(sizeof(char), max_len + 1);
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\n')
			line[i] = '1';
		else
			line[j] = str[i];
		j++;
		i++;
	}
	if (j < max_len)
	{
		while (j < max_len)
			line[j++] = '1';
		line[j] = '\0';
	}
	return (line);
}

void	make_map_rectangular(char **map, t_map_info *map_info)
{
	char	*line;
	size_t	row_len;
	size_t	x;

	row_len = longest_row(map);
	x = 0;
	while (map[x])
		x++;
	map_info->x = x;
	map_info->y = row_len;
	map_info->map = ft_calloc(sizeof(char *), x + 1);
	x = 0;
	while (map[x])
	{
		line = fix_line(map[x], row_len);
		map_info->map[x] = ft_strdup(line);
		free(line);
		x++;
	}
}
