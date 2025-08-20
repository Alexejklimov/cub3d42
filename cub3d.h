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

// # include "libraries/minilibx-linux/mlx.h"
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

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define PXL 16 ///////////////

# define WIDTH 1024
# define HEIGHT 800


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
	size_t		x; // heigth 
	size_t		y; // width
	char		**map;
	int			start_pos[2];
	char		start_orient;
	char		*texture[4];
	int			floor_rgb[3];
	int			ceil_rgb[3];
}	t_map_info;

typedef struct s_raycast
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delt_dist_x;
	double	delt_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
	int		map_x;
	int		map_y;
	int		wall_height;
	int		wall_start;
	int		wall_end;
}			t_raycast;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	mlx_image_t	*wall_image;
	void		*win_mlx;//
	t_map_info	*map_info;
	t_player	player;
	double		move_speed;
	double		move_rotate;
	double		oldtime;
	double		first_frame;
	int			**map;
}				t_game;

typedef enum e_texture
{
	NORD,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEIL
}	t_texture;

//parsing of map

char			**read_map(char *map_file);
void			rgb_parse(char *line, int *dest);
int				parse_texture(char **file, t_map_info *map_info);
char			**separate_map(char **file, t_map_info *map_info);
void			parse_map(char *file, t_map_info *map_info);
int				verify_texture(t_map_info *map);
void			check_map_is_valid(char **map, t_map_info *map_info);
int				is_symbols_valid_only(char **map);
int				check_walls_is_valid(char **map);
void			make_map_rectangular(char **map, t_map_info *map_info);
void			free_map(char **map);
void			fill_start_pos_orient(t_map_info *map_info);
void			texture_end_fixer(t_map_info *map);
void			fill_start_pos_orient(t_map_info *map_info);
size_t			longest_row(char	**map);
char			*fix_line(char	*str, size_t max_len);

#endif