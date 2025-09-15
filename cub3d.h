/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:31:28 by oklimov           #+#    #+#             */
/*   Updated: 2025/07/15 15:06:52 by oklimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libraries/printf/ft_printf.h"
# include "libraries/MLX42/include/MLX42/MLX42.h"
# include "libraries/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/time.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

// # define SCREEN_WIDTH 800
# define SCREEN_WIDTH 1280
// # define SCREEN_HEIGHT 600
# define SCREEN_HEIGHT 1024
# define MINI_MAP_RAYS 200

typedef struct s_point
{
	int	x;
	int	y;
}		t_point;

typedef struct s_vector
{
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
}			t_vector;

typedef struct s_minimap
{
	int		x;
	int		y;
	int		size;
	int		max_size;
	int		player_x;
	int		player_y;
	int		scale;
	int		mheight;
	int		mwidth;
	t_point	player;
}		t_minimap;

typedef struct s_player
{
	double	x;			// позиция x
	double	y;			// позиция y  
	double	angle;		// угол поворота
	double	plane_x;	// угол поворота
	double	plane_y;	// угол поворота
	double	dx;			// направление x (cos угла)
	double	dy;			// направление y (sin угла)
}			t_player;

typedef struct s_map_info
{
	size_t	x; // heigth 
	size_t	y; // width
	char	**map;
	char	start_orient;
	int		start_pos[2];
	char	*texture[4];
	int		floor_rgb[3];
	int		ceil_rgb[3];
}			t_map_info;

typedef struct s_wall
{
	int		height;
	int		start;
	int		end;
	int		tex_x;
	int		tex_y;
	double	wall_x;
	double	brightness;
	double	tex_step;
	double	tex_pos;
}			t_wall;

typedef struct s_raycast
{
	double	camera_x;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perpwalldist;
	int		step_x;
	int		step_y;
	int		side;
	int		map_x;
	int		map_y;
	int		wall_height;
	int		wall_start;
	int		wall_end;
	t_wall	wall;
}			t_raycast;

typedef struct s_tex_info
{
	xpm_t		*nord_tex;
	xpm_t		*south_tex;
	xpm_t		*west_tex;
	xpm_t		*east_tex;
	mlx_image_t	texture[4];
	mlx_image_t	*nwall;
	mlx_image_t	*swall;
	mlx_image_t	*ewall;
	mlx_image_t	*wwall;
}				t_tex_info;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	mlx_image_t	*wall_image;
	mlx_image_t	*walls[4];
	void		*win_mlx;//
	t_map_info	*map_info;
	uint32_t	ceil_color;
	uint32_t	floor_color;
	t_player	player;
	double		move_speed;
	double		move_rotate;
	double		oldtime;
	double		first_frame;
	int			**map;
	int			map_width;
	int			map_height;
	t_minimap	minimap;
}				t_game;

typedef enum e_texture
{
	NORD = 3,
	SOUTH = 2,
	WEST = 1,
	EAST = 0,
	FLOOR,
	CEIL
}	t_texture;

//=			Parsing		=//

char		**read_map(char *map_file);
int			rgb_parse(char *line, int *dest);
int			parse_texture(char **file, t_map_info *map_info);
char		**separate_map(char **file, t_map_info *map_info);
void		parse_map(char *file, t_map_info *map_info);
int			verify_texture(t_map_info *map);
int			check_map_is_valid(char **map, t_map_info *map_info);
int			is_symbols_valid_only(char **map);
int			check_walls_is_valid(char **map);
void		clean_map_info(t_map_info *map_info);
int			map_info_fill_checker(t_map_info *map);
int			ft_check_arg(char *mapname, char *ber, int length);
void		make_map_rectangular(char **map, t_map_info *map_info);
void		free_map(char **map);
void		fill_start_pos_orient(t_map_info *map_info);
void		texture_end_fixer(t_map_info *map);
void		fill_start_pos_orient(t_map_info *map_info);
size_t		longest_row(char	**map);
char		*fix_line(char	*str, size_t max_len);

//=			Render utils	=//

uint32_t	get_texture_color(mlx_image_t *texture, int tex_x, int tex_y);
uint32_t	apply_brightness(uint32_t color, double brightness, int alpha);
uint32_t	create_color(int r, int g, int b, int a);
void		put_pixel(mlx_image_t *image, int x, int y, uint32_t color);

//=			Utils	=//

void		panic(char *s);

#endif