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

# include "../libraries/printf/ft_printf.h"
# include "../libraries/libft/libft.h"
# include "MLX42.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/time.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 1024
# define MINI_MAP_RAYS 200

# ifndef BONUS
#  define BONUS 0
# endif

typedef struct s_point
{
	int	x;
	int	y;
}		t_point;

typedef struct s_camera
{
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
}			t_camera;

typedef struct s_minimap
{
	int		x;
	int		y;
	int		size;
	int		max_size;
	int		scale;
	int		player_x;
	int		player_y;
	int		mheight;
	int		mwidth;
	t_point	player;
}			t_minimap;

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
	int			height;
	int			start;
	int			end;
	int			tex_x;
	int			tex_y;
	double		wall_x;
	double		brightness;
	double		tex_step;
	double		tex_pos;
	mlx_image_t	*image;
}				t_wall;

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
	t_wall	wall;
}			t_raycast;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	mlx_image_t	*walls[4];
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
	NORD = 0,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEIL
}	t_texture;

//======	Parsing		======//

char		**read_map(char *map_file);
int			rgb_parse(char *line, int *dest);
int			parse_texture(char **file, t_map_info *map_info);
char		**separate_map(char **file, t_map_info *map_info);
void		parse_map(char *file, t_map_info *map_info);
int			verify_texture(t_map_info *map);
int			check_map_is_valid(char **map, t_map_info *map_info);
int			is_symbols_valid_only(char **map);
int			check_walls_is_valid(char **map);
int			ft_check_arg(char *mapname, char *ber, int length);
void		clean_map_info(t_map_info *map_info);
int			map_info_fill_checker(t_map_info *map);

void		make_map_rectangular(char **map, t_map_info *map_info);
void		free_map(char **map);
void		fill_start_pos_orient(t_map_info *map_info);
void		texture_end_fixer(t_map_info *map);
void		fill_start_pos_orient(t_map_info *map_info);
size_t		longest_row(char	**map);
char		*fix_line(char	*str, size_t max_len);

//======	Render utils				======//

uint32_t	get_tex_color(mlx_image_t *texture, int tex_x, int tex_y);
uint32_t	apply_brightness(uint32_t color, double brightness, int alpha);
uint32_t	create_color(int r, int g, int b, int a);
void		put_pixel(mlx_image_t *image, int x, int y, uint32_t color);

//====		Utils						======//

double		ft_get_time(void);
void		panic(char *s);
void		errexit(t_game *game, char *msg);

//=========	Raycasting and render		======//

mlx_image_t	*get_curr_texture(t_game *game, t_raycast *ray);
double		calculate_wall_brightness(t_raycast *ray);
void		render(t_game *game, int x, t_raycast *ray, t_wall *wall);
void		prepare_wall_render(t_game *game, t_raycast *ray, t_wall *wall);
void		compute_wall_hit_position(t_raycast *ray, t_wall *wall);
int			step_texture_y(t_wall *wall);
void		game_loop(void *param);
int			init(t_game *game);
void		init_mlx(t_game *game);
void		raycast(t_game *game);
void		handle_movement(t_game *game);

//==		Bonus						======//
void		render_mini_map(t_game *game);

#endif
