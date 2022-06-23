/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:40:08 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/23 12:53:39 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
// STDIO to remove

# include "../libft/libft.h"
# include "../mlx/mlx.h"

typedef enum e_orientation
{
	NORTH,
	WEST,
	EAST,
	SOUTH
}			t_orientation;

typedef struct s_pos
{
	double		x;
	double		y;
}				t_pos;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	t_orientation	orientation;
}				t_player;

typedef struct s_screen
{
	int	width;
	int	height;
}				t_screen;

typedef struct s_text
{
	void	*img;
	int		*addr;
	int		img_width;
	int		img_height;
	int		size_line;
	int		endian;
	int		bits_per_pixel;
}				t_text;

typedef struct s_sprites
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
}				t_sprites;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlx;

typedef struct s_algo
{
	t_pos	dir;
	t_pos	plane;
	t_pos	ray_pos;
	t_pos	ray_dir;
	t_pos	dist;
	t_pos	map;
	t_pos	side_dist;
	t_pos	delta_dist;
	t_pos	step;
	int		**buffer;
	int		side;
	int		hit;
	double	perp_wall_dist;
	double	camera_x;
	double	move_speed;
	double	rot_speed;
}				t_algo;

typedef struct s_data
{
	t_screen	screen;
	t_player	player;
	t_sprites	sprites;
	t_mlx		mlx;
	t_algo		algo;
	t_text		*text;
	char		*buf;
	char		**map;
	int			**texture;
	int			floor_color;
	int			ceiling_color;
}				t_data;


/***************************/
/*						   */
/*        ALGORITHM        */
/*						   */
/***************************/

/*	INPUT.C		*/

int		input(int key, t_data *data);
/*	PARSING.C	*/

int		usless_line(char *str);
void	parsing(char *name, t_data *data);

/*	UTILS.C	*/

int		open_map(char *name);
void	error(char *str, int i);
void	free_all(char **str);

/*	DRAW.C	*/

void	draw(t_data *data);
void	draw_line(t_data *data, t_pos start, t_pos end, int color);
void	pixel_put(t_data *data, int x, int y, int color);

/*	PARSING.C	*/

void	parsing(char *name, t_data *data);

/*	START.C	*/

void	start(t_data *data);

/*	TEXTURES.C	*/

void	load_textures(t_data *data);
void	apply_textures(t_data *data);
/*	GET_PATH	*/

void	get_map(int fd, t_data *data, size_t max_len);

/*	UTILS.C	*/

void	error(char *str, int i);
void	free_all(char **str);
int		is_power_of_two(int x);

#endif