/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_separate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:02:27 by oklimov           #+#    #+#             */
/*   Updated: 2025/07/21 15:02:27 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	**read_map(char *map_file)
{
	int			fd;
	int			i;
	char		*line;
	char		**map;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (perror("open map file - Error\n"), NULL);
	map = malloc(sizeof(char *) * 108);
	if (!map)
		return (perror("map memory allocate - Error\n"), NULL);
	line = " ";
	i = 0;
	while (line != NULL)
	{
		line = get_next_line(fd);
		map[i] = line;
		i++;
	}
	close(fd);
	map[i] = NULL;
	return (map);
}

void	rgb_parse(char *line, int *dest)
{
	int	i;
	int	texture_index;
	int	buffer;

	buffer = 0;
	i = 0;
	texture_index = 0;
	while (line[i] && texture_index < 3)
	{
		buffer = 0;
		while (ft_isdigit(line[i]))
			buffer = (buffer * 10) + (line[i++] - '0');
		if (buffer)
			dest[texture_index++] = buffer;
		i++;
	}
}

int	verify_texture(t_map_info *map)
{
	int	i;
	int	fd;

	i = 0;
	texture_end_fixer(map);
	while (i < 4)
	{
		fd = open(map->texture[i], O_RDONLY);
		close(fd);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (!(map->ceil_rgb[i] >= 0 && map->ceil_rgb[i] <= 255
				&& map->floor_rgb[i] && map->floor_rgb[i] >= 0
				&& map->floor_rgb[i] <= 255))
			return (0);
		i++;
	}
	return (1);
}

int	parse_texture(char **file, t_map_info *map_info)
{
	int	i;

	i = 0;
	while (file[i][0] != '1' && file[i][0] != ' ' && file[i][0] != '\t')
	{
		if (ft_strlen(file[i]) == 0)
			i++;
		if (!ft_strncmp((char *)file[i], "NO", 2))
			map_info->texture[0] = ft_strdup(file[i] + 3);
		if (!ft_strncmp((char *)file[i], "SO", 2))
			map_info->texture[1] = ft_strdup(file[i] + 3);
		if (!ft_strncmp((char *)file[i], "WE", 2))
			map_info->texture[2] = ft_strdup(file[i] + 3);
		if (!ft_strncmp((char *)file[i], "EA", 2))
			map_info->texture[3] = ft_strdup(file[i] + 3);
		if (!ft_strncmp((char *)file[i], "F", 1))
			rgb_parse(file[i] + 2, map_info->floor_rgb);
		if (!ft_strncmp((char *)file[i], "C", 1))
			rgb_parse(file[i] + 2, map_info->ceil_rgb);
		i++;
	}
	return (i);
}

char	**separate_map(char **file, t_map_info *map_info)
{
	int			i;
	int			j;
	int			acc;
	char		**separated_map;

	i = parse_texture(file, map_info);
	acc = i;
	while (file[acc] != NULL)
		acc++;
	separated_map = malloc(sizeof(char *) * acc);
	j = 0;
	while (file[i])
		separated_map[j++] = ft_strdup(file[i++]);
	separated_map[j] = NULL;
	i = 0;
	free_map(file);
	return (separated_map);
}
