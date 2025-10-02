/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:42:16 by oklimov           #+#    #+#             */
/*   Updated: 2025/10/02 14:43:51 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		return (0);
	return (i);
}

void	is_end_of_file(char **file, char **separated_map, int i)
{
	while (file[i])
	{
		if (file[i][0] != '\n')
		{
			free_map(separated_map);
			free_map(file);
			panic("Error\nextra symbol after map");
		}
		i++;
	}
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
	while (file[i] && file[i][0] != '\n')
		separated_map[j++] = ft_strdup(file[i++]);
	separated_map[j] = NULL;
	is_end_of_file(file, separated_map, i);
	return (free_map(file), separated_map);
}
