#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <math.h>
# include "../LIBFT_GNL/libft.h"
# include "../LIBFT_GNL/get_next_line/get_next_line.h"

# define C_R    8
# define C_NO   0
# define C_SO   1
# define C_WE   2
# define C_EA   3
# define C_C    5
# define C_F    6
# define C_MAP  7

# define TEXTURES 5
# define T_NO 0
# define T_SO 1
# define T_WE 2
# define T_EA 3
# define T_S 4
# define T_C 5
# define T_F 6

typedef struct s_config
{
	int			win_width;
	int			win_height;
	char		*tex_path[TEXTURES];
	int			cf_color[2];
	char		**map;
	char		**map_c;
	int			map_row;
	int			map_col;
	int			pos_x;
	int			pos_y;
	char		dir;
	int			set[8];
}	t_config;

/*
	status_define
*/

# define EXIT_FAILURE	1
# define EXIT_SUCCESS	0
# define WIDTH
# define HEIGHT
# define SPEED
# define ROTATE_SPPED
# define FOV			0.66

/*
	key_event define
*/

# define KEY_ESC  53
# define KEY_W	13
# define KEY_A	0
# define KEY_S	1
# define KEY_D	2
# define KEY_UP   126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define LEFT -1
# define RIGHT 1

typedef struct s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	int			width;
	int			height;
}	t_img;

typedef struct s_map
{
	int		fd;
	int		wid;
	int		hei;
	int		flags;

	t_img	imgs[4];
	t_rgb	floor;
	t_rgb	ceiling;

	t_list	*list;
	char	**map;
}	t_map;

typedef struct	s_key
{
	int			right;
	int			left;
	int			w;
	int			s;
	int			a;
	int			d;
}				t_key;

/*
	data
*/

typedef struct s_data
{
	void		*mlx_ptr;
	void		*mlx_win;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		pln_x;
	double		pln_y;
	double		move_speed;
	double		rotation_speed;

	t_img		img;
	t_key		key;
	t_config	*config;
}				t_data;

typedef struct	s_vetor
{
	double		r_dir_x;
	double		r_dir_y;
	double		side_dst_x;
	double		side_dst_y;
	double		delt_dst_x;
	double		delt_dst_y;
	double		prp_wal_dst;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
}				t_vector;

typedef struct	s_back_line
{
	int			l_height;
	int			draw_strt;
	int			draw_end;
	int			color;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	int			tex_num;
	double		flr_x_wall;
	double		flr_y_wall;
	int			flr_tex_x;
	int			flr_tex_y;
}				t_back_line;

typedef struct	s_pair
{
	double		dist;
	int			order;
}				t_pair;

typedef struct		s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;




/*
	03_draw.c
*/

int		start_game(t_data *data)
int		game_close(t_data *data)
void	draw(t_data *data)
void	clear_game(t_data *data, int status)
void	calc_back(t_data *data)
void	calc_vars(int x, t_vector *vec, t_data *data)
void	calc_dists(t_vector *vec, t_data *data)
void	ray_cast(t_vector *vec, t_data *data)
void	calc_line(t_back_line *line, t_vector *vec, t_data *data)
void	calc_wall(t_back_line *line, t_vector *vec, t_data *data)
void	coord_wall_tex(int x, t_back_line *line, t_data *data)
void	calc_floor(t_back_line *line, t_vector *vec)
void	coord_floor_color(int x, t_back_line *line, t_data *data)

/*
	04_key.c
*/

int		key_update(t_data *data)
int		key_press(int key, t_data *data)
int		key_release(int key, t_data *data)

/*
	05_move.c
*/

void	move_vertical(t_data *data, int direction)
void	move_horizontal(t_data *data, int direction)
void	rotate(t_data *data, int direction)


/*
	09_utils.c
*/

void	screen_size(void *mlx, int *width, int *height)
void	error(t_data *data, char *err_msg, int status)
#endif
