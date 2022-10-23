/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonkim <wonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 12:18:16 by wonkim            #+#    #+#             */
/*   Updated: 2022/10/23 12:19:34 by wonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/cub3d.h"

int		tex_init(t_data *data)
{
	int i;
	int j;

	data->texture = (int **)malloc(sizeof(int *) * TEXTURES);
	if (!(data->texture))
		return (-1);
	i = 0;
	while (i < TEXTURES)
	{
		data->texture[i] = (int *)malloc(sizeof(int) *
				(TEX_HEIGHT * TEX_WIDTH));
		if (!(data->texture[i]))
		{
			tex_free(data, i);
			return (-1);
		}
		j = 0;
		while (j < TEX_HEIGHT * TEX_WIDTH)
		{
			data->texture[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}

void	load_image(t_data *data, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, path,
			&img->width, &img->height);
	if (!(img->img_ptr))
		error_exit(data, "Error: texture loading failed\n", 1);
	img->data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->size_l, &img->endian);
	if (!(img->data))
		error_exit(data, "Error: texture data loading failed\n", 1);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			texture[img->width * y + x] = img->data[img->width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(data->mlx_ptr, img->img_ptr);
}

void	load_texture(t_data *data)
{
	t_img	img;

	load_image(data, data->texture[T_NO], data->config->tex_path[T_NO], &img);
	load_image(data, data->texture[T_SO], data->config->tex_path[T_SO], &img);
	load_image(data, data->texture[T_WE], data->config->tex_path[T_WE], &img);
	load_image(data, data->texture[T_EA], data->config->tex_path[T_EA], &img);
}

void	tex_free(t_data *data, int i)
{
	while (i >= 0)
	{
		free(data->texture[i]);
		i--;
	}
	free(data->texture);
}
