#ifndef CUB3G_H
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

# define MOVE_LEFT		0
# define MOVE_RIGHT		2
# define MOVE_DOWN		1
# define MOVE_UP		13
# define ROTATE_LEFT	123
# define ROTATE_RIGHT	124
# define ESCAPE			53
# define WINDOW_ESCAPE	17

/*
	img
*/

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

/*
	rgb_color
*/

typedef struct s_color
{
	unsigned char	blue;
	unsigned char	green;
	unsigned char	red;
	unsigned char	t;
}	t_color;
