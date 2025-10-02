/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:42:16 by oklimov           #+#    #+#             */
/*   Updated: 2025/10/02 14:50:41 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

int	check_map_is_valid(char **map, t_map_info *map_info)
{
	if (!is_symbols_valid_only(map))
		return (0);
	if (!verify_texture(map_info))
		return (ft_printf("Error\nTexture data not valid\n"), 0);
	if (!check_walls_is_valid(map))
		return (ft_printf("Error\nWalls is invalid\n"), 0);
	make_map_rectangular(map, map_info);
	return (1);
}
