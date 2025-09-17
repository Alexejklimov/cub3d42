/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:45:49 by nmagomad          #+#    #+#             */
/*   Updated: 2025/09/17 15:17:50 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	apply_brightness(uint32_t color, double brightness, int alpha)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = (color) & 0xFF;
	r = (int)(r * brightness);
	g = (int)(g * brightness);
	b = (int)(b * brightness);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (create_color(r, g, b, alpha));
}

uint32_t	get_tex_color(mlx_image_t *texture, int tex_x, int tex_y)
{
	uint8_t	*pixel;

	if (tex_x < 0 || tex_x >= (int)texture->width
		|| tex_y < 0 || tex_y >= (int)texture->height)
		return (0xFF000000);
	pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
	return (((uint32_t)pixel[3] << 24)
		| ((uint32_t)pixel[0] << 16)
		| ((uint32_t)pixel[1] << 8)
		| (uint32_t)pixel[2]);
}

uint32_t	create_color(int r, int g, int b, int a)
{
	return ((uint32_t)r << 24
		| (uint32_t)g << 16
		| (uint32_t)b << 8
		| (uint32_t)a);
}
