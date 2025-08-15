/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:31:57 by oklimov           #+#    #+#             */
/*   Updated: 2025/08/08 15:05:24 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// void	clean_and_exit(t_map_info *map_info)
// {

// }

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
	map = NULL;
}
