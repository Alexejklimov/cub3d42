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
	map = malloc(sizeof(char *) * 256);
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
	if (i == 0)
		printf("error\nempty file");
	return (map);
}

int	is_valid_rgb_data(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\n')
		return (0);
	while (line[i] && line[i] != '\n' && line[i] != '\0')
	{
		if (!ft_isdigit(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	rgb_parse(char *line, int *dest)
{
	char	**split_arr;
	int		i;

	split_arr = ft_split(line, ',');
	if (!split_arr)
		panic("malloc problem");
	i = 0;
	while (split_arr[i])
		i++;
	if (i != 3)
			panic("Error\ncolor info incorrect");
	i = 0;
	while (i < 3)
	{
		if (is_valid_rgb_data(split_arr[i]))
			dest[i] = ft_atoi(split_arr[i]);
		else
			panic("Error\nrgb color incorrect");
		i++;
	}
	if (i != 3)
		panic("\nkaka\n");
	free_map(split_arr);
	return (1);
}

int	verify_texture(t_map_info *map)
{
	int	i;
	int	fd;

	i = 0;
	texture_end_fixer(map);
	while (i < 4)
	{
		fd = 0;
		fd = open(map->texture[i], O_RDONLY);
		if (fd < 0)
			return (printf("Error\ncannot open file\n"), 0);
		close(fd);
		if (ft_check_arg(map->texture[i], ".xpm42", 6))
			return (printf("Error\ntexture file incorrect"), 0);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (!(map->ceil_rgb[i] >= 0 && map->ceil_rgb[i] <= 255
				&& map->floor_rgb[i] >= 0 && map->floor_rgb[i] <= 255))
			return (0);
		i++;
	}
	return (1);
}

int	fill_texture_struct(t_map_info *map, char *line, int num)
{
	char	*start;

	while (*line == ' ' || *line == '\t')
		line++;
	start = line;
	while (*line)
	{
		if (*line == ' ' || *line == '\t' || *line == '\r')
		{
			*line = '\0';
			break ;
		}
		line++;
	}
	map->texture[num] = ft_strdup((const char *)start);
	return (1);
}

int	parse_texture(char **file, t_map_info *map_info)
{
	int	i;
	int	acc;

	i = 0;
	while (file[i] != NULL && file[i][0] != '1' && file[i][0] != ' '
		&& file[i][0] != '\t')
	{
		if (!ft_strncmp((char *)file[i], "NO ", 3))
			acc = fill_texture_struct(map_info, file[i] + 2, 0);
		if (!ft_strncmp((char *)file[i], "SO ", 3))
			acc += fill_texture_struct(map_info, file[i] + 2, 1);
		if (!ft_strncmp((char *)file[i], "WE ", 3))
			acc += fill_texture_struct(map_info, file[i] + 2, 2);
		if (!ft_strncmp((char *)file[i], "EA ", 3))
			acc += fill_texture_struct(map_info, file[i] + 2, 3);
		if (!ft_strncmp((char *)file[i], "F ", 2))
			acc += rgb_parse(file[i] + 2, map_info->floor_rgb);
		if (!ft_strncmp((char *)file[i], "C ", 2))
			acc += rgb_parse(file[i] + 2, map_info->ceil_rgb);
		i++;
	}
	if (acc != 6)
		return ( 0);
	return (i);
}

char	**separate_map(char **file, t_map_info *map_info)
{
	int			i;
	int			j;
	int			acc;
	char		**separated_map;

	i = 0;
	while (i < 3)
	{
		map_info->floor_rgb[i] = -1;
		map_info->ceil_rgb[i] = -1;
		i++;
	}
	i = parse_texture(file, map_info);
	if (i == 0)
		return (printf("Error\nincorrect file info"), free_map(file), NULL);
	acc = i;
	while (file[acc] != NULL)
		acc++;
	separated_map = malloc(sizeof(char *) * acc);
	j = 0;
	while (file[i])
		separated_map[j++] = ft_strdup(file[i++]);
	separated_map[j] = NULL;
	free_map(file);
	return (separated_map);
}
