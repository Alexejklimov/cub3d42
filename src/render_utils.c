/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagomad <nmagomad@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:45:50 by nmagomad          #+#    #+#             */
/*   Updated: 2025/08/24 15:55:30 by nmagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Puts a pixel of a specified color at given coordinates in an image.
 *
 * This function sets the pixel at coordinates (x, y) to the given color
 * if the coordinates are within the bounds of the image. If the coordinates
 * are outside the image dimensions, the function does nothing.
 *
 * @param image Pointer to the image structure where the pixel will be set.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color value to set the pixel to.
 */
void	put_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	if (x >= 0 && x < (int)image->width && y >= 0 && y < (int)image->height)
	{
		mlx_put_pixel(image, x, y, color);
	}
}

/**
 * @brief Creates a 32-bit color value from individual RGBA components.
 *
 * This function takes separate red, green, blue, and alpha components
 * (each ranging from 0 to 255) and packs them into a single 32-bit
 * unsigned integer in the format: 0xRRGGBBAA.
 *
 * @param r Red component (0-255).
 * @param g Green component (0-255).
 * @param b Blue component (0-255).
 * @param a Alpha (transparency) component (0-255).
 * @return A 32-bit unsigned integer representing the combined RGBA color.
 */
uint32_t	create_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * @brief Applies brightness adjustment to a given color.
 *
 * This function extracts the red, green, and blue components from a 32-bit
 * color, multiplies them by the brightness factor, clamps the results to
 * the valid range [0, 255], and returns a new color with the specified alpha.
 *
 * @param color The original 32-bit color in 0xRRGGBBAA format.
 * @param brightness Brightness factor to apply
 *        (e.g., 1.0 = original, 0.5 = half brightness).
 * @param alpha Alpha (transparency) value to use in the resulting color (0-255).
 * @return A 32-bit color with adjusted brightness and specified alpha.
 */
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

/**
 * @brief Retrieves the color of a pixel from a texture image.
 *
 * This function accesses the pixel data of a texture and returns the color
 * at the specified coordinates. If the coordinates are out of bounds, it
 * returns opaque black (0xFF000000).
 *
 * @param texture Pointer to the texture image structure.
 * @param tex_x X-coordinate of the pixel within the texture.
 * @param tex_y Y-coordinate of the pixel within the texture.
 * @return The 32-bit color of the pixel in 0xRRGGBBAA format.
 */
uint32_t	get_texture_color(mlx_image_t *texture, int tex_x, int tex_y)
{
	uint8_t	*pixel;

	if (tex_x < 0 || tex_x >= (int)texture->width
		|| tex_y < 0 || tex_y >= (int)texture->height)
		return (0xFF000000);
	pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
	return ((pixel[3] << 24) | (pixel[0] << 16) | (pixel[1] << 8) | pixel[2]);
}
