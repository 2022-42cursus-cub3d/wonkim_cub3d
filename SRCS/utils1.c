#include "../INC/cub3d.h"

void	screen_size(void *mlx, int *width, int *height)
{
	int sizex;
	int	sizey;

	mlx_get_screen_size(mlx, &sizex, &sizey);
	if (sizex < *width)
		*width = sizex;
	if (sizey < *height)
		*height = sizey;
}

void	error(t_data *data, char *err_msg, int status)
{
	write(2, "Error:\n", 7);
	write(2, err_msg, ft_strlen(err_msg));
	clear_game(data, status);
	exit(-1);
	return (-1);
}
