#include "../INC/cub3d.h"

void	ptr_init(t_data *data)
{
	data->buf = 0;
	data->texture = 0;
	data->z_buf = 0;
	data->img.img_ptr = 0;
	data->img.data = 0;
	data->mlx = 0;
	data->win = 0;
	data->sprite = 0;
}

void	dir_init(t_data *data)
{
	if (data->config.dir == 'N')
	{
		data->dir_y = -1;
		data->pln_x = 0.66;
	}
	else if (data->config.dir == 'S')
	{
		data->dir_y = 1;
		data->pln_x = -0.66;
	}
	else if (data->config.dir == 'W')
	{
		data->dir_x = -1;
		data->pln_y = -0.66;
	}
	else
	{
		data->dir_x = 1;
		data->pln_y = 0.66;
	}
}

int		buf_init(t_data *data)
{
	int i;
	int j;

	data->buf = (int**)malloc(sizeof(int*) * data->config.win_height);
	if (!(data->buf))
		return (-1);
	i = 0;
	while (i < data->config.win_height)
	{
		data->buf[i] = (int*)malloc((sizeof(int) * data->config.win_width));
		if (!(data->buf[i]))
		{
			buf_free(data, i);
			return (-1);
		}
		j = 0;
		while (j < data->config.win_width)
		{
			data->buf[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}

void	key_init(t_data *data)
{
	data->key.right = 0;
	data->key.left = 0;
	data->key.w = 0;
	data->key.s = 0;
	data->key.a = 0;
	data->key.d = 0;
}

int		data_init(t_data *data)
{
	data->pos_x = data->config.pos_x + 0.5;
	data->pos_y = data->config.pos_y + 0.5;
	data->dir_x = 0;
	data->dir_y = 0;
	data->pln_x = 0;
	data->pln_y = 0;
	data->score = 0;
	dir_init(data);
	data->mv_speed = 0.05;
	data->rot_speed = 0.05;
	key_init(data);
	if (buf_init(data) == -1 || tex_init(data) == -1)
		return (-1);
	data->z_buf = (double*)malloc(sizeof(double) * data->config.win_width);
	return (0);
}
