/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonkim <wonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:57:00 by wonkim            #+#    #+#             */
/*   Updated: 2022/10/20 15:49:54 by wonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/cub3d.h"

int		start_game(t_data *data)
{
	calc_back(data);
	draw(data);
	key_update(data);
	return (0);
}

int		game_close(t_data *data)
{
	printf("> exit game\n");
	clear_game(data, 1);
	exit(0);
}

void	draw(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->config.win_height)
	{
		x = 0;
		while (x < data->config.win_width)
		{
			data->img.data[y * data->config.win_width + x] = data->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

void	clear_game(t_data *data, int status)
{
	if (data)
	{
		if (status != 0)
			clear_config(data->config, status);
		if (data->buf)
			buf_free(data, data->config.win_height - 1);
		if (data->texture)
			tex_free(data, TEXTURES - 1);
		if (data->z_buf)
			free(data->z_buf);
		clear_window(data);
	}
}

void	calc_back(t_data *data)
{
	t_vector	vec;
	t_back_line	line;
	int			x;

	x = 0;
	while (x < data->config.win_width)
	{
		calc_vars(x, &vec, data);
		calc_dists(&vec, data);
		ray_cast(&vec, data);
		calc_line(&line, &vec, data);
		calc_wall(&line, &vec, data);
		coord_wall_tex(x, &line, data);
		calc_floor(&line, &vec);
		coord_floor_color(x, &line, data);
		data->z_buf[x] = vec.prp_wal_dst;
		x++;
	}
}

void	calc_vars(int x, t_vector *vec, t_data *data)
{
	double	camera_x;

	camera_x = 2 * x / (double)data->config.win_width - 1;
	vec->r_dir_x = data->dir_x + data->pln_x * camera_x;
	vec->r_dir_y = data->dir_y + data->pln_y * camera_x;
	vec->map_x = (int)data->pos_x;
	vec->map_y = (int)data->pos_y;
	vec->delt_dst_x = fabs(1 / vec->r_dir_x);
	vec->delt_dst_y = fabs(1 / vec->r_dir_y);
}

void	calc_dists(t_vector *vec, t_data *data)
{
	if (vec->r_dir_x < 0)
	{
		vec->step_x = -1;
		vec->side_dst_x = (data->pos_x - vec->map_x) * vec->delt_dst_x;
	}
	else
	{
		vec->step_x = 1;
		vec->side_dst_x = (vec->map_x + 1.0 - data->pos_x) * vec->delt_dst_x;
	}
	if (vec->r_dir_y < 0)
	{
		vec->step_y = -1;
		vec->side_dst_y = (data->pos_y - vec->map_y) * vec->delt_dst_y;
	}
	else
	{
		vec->step_y = 1;
		vec->side_dst_y = (vec->map_y + 1.0 - data->pos_y) * vec->delt_dst_y;
	}
}

void	ray_cast(t_vector *vec, t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (vec->side_dst_x < vec->side_dst_y)
		{
			vec->side_dst_x += vec->delt_dst_x;
			vec->map_x += vec->step_x;
			vec->side = X_PLANE;
		}
		else
		{
			vec->side_dst_y += vec->delt_dst_y;
			vec->map_y += vec->step_y;
			vec->side = Y_PLANE;
		}
		if (data->config.map[vec->map_x][vec->map_y] == '1')
			hit = 1;
	}
}

void	calc_line(t_back_line *line, t_vector *vec, t_data *data)
{
	if (vec->side == X_PLANE)
	{
		vec->prp_wal_dst = (vec->map_x - data->pos_x + (1 - vec->step_x) / 2);
		vec->prp_wal_dst /= vec->r_dir_x;
	}
	else
	{
		vec->prp_wal_dst = (vec->map_y - data->pos_y + (1 - vec->step_y) / 2);
		vec->prp_wal_dst /= vec->r_dir_y;
	}
	line->l_height = (int)(data->config.win_height / vec->prp_wal_dst);
	line->draw_strt = -(line->l_height) / 2 + data->config.win_height / 2;
	if (line->draw_strt < 0)
		line->draw_strt = 0;
	line->draw_end = line->l_height / 2 + data->config.win_height / 2;
	if (line->draw_end >= data->config.win_height)
		line->draw_end = data->config.win_height - 1;
}

void	calc_wall(t_back_line *line, t_vector *vec, t_data *data)
{
	if (vec->side == X_PLANE && vec->step_x == 1)
		line->tex_num = T_EA;
	else if (vec->side == X_PLANE && vec->step_x == -1)
		line->tex_num = T_WE;
	else if (vec->side == Y_PLANE && vec->step_y == 1)
		line->tex_num = T_SO;
	else
		line->tex_num = T_NO;
	if (vec->side == 0)
		line->wall_x = data->pos_y + vec->prp_wal_dst * vec->r_dir_y;
	else
		line->wall_x = data->pos_x + vec->prp_wal_dst * vec->r_dir_x;
	line->wall_x -= floor(line->wall_x);
	line->tex_x = (int)(line->wall_x * (double)TEX_WIDTH);
	if (vec->side == 0 && vec->r_dir_x > 0)
		line->tex_x = TEX_WIDTH - line->tex_x - 1;
	if (vec->side == 1 && vec->r_dir_y < 0)
		line->tex_x = TEX_WIDTH - line->tex_x - 1;
}

void	coord_wall_tex(int x, t_back_line *line, t_data *data)
{
	double	step;
	double	tex_pos;
	int		tex_tmp;
	int		y;

	step = 1.0 * TEX_HEIGHT / line->l_height;
	tex_pos = (line->draw_strt - data->config.win_height
				/ 2 + line->l_height / 2) * step;
	y = line->draw_strt;
	while (y < line->draw_end)
	{
		line->tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		tex_tmp = TEX_WIDTH * line->tex_y + line->tex_x;
		line->color = data->texture[line->tex_num][tex_tmp];
		data->buf[y][x] = line->color;
		y++;
	}
}

void	calc_floor(t_back_line *line, t_vector *vec)
{
	if (vec->side == X_PLANE && vec->r_dir_x > 0)
	{
		line->flr_x_wall = vec->map_x;
		line->flr_y_wall = vec->map_y + line->wall_x;
	}
	else if (vec->side == X_PLANE && vec->r_dir_x < 0)
	{
		line->flr_x_wall = vec->map_x + 1.0;
		line->flr_y_wall = vec->map_y + line->wall_x;
	}
	else if (vec->side == Y_PLANE && vec->r_dir_y > 0)
	{
		line->flr_x_wall = vec->map_x + line->wall_x;
		line->flr_y_wall = vec->map_y;
	}
	else
	{
		line->flr_x_wall = vec->map_x + line->wall_x;
		line->flr_y_wall = vec->map_y + 1.0;
	}
}

void	coord_floor_color(int x, t_back_line *line, t_data *data)
{
	int		y;

	if (line->draw_end < 0)
		line->draw_end = data->config.win_height;
	y = line->draw_end + 1;
	while (y < data->config.win_height)
	{
		data->buf[y][x] = data->config.cf_color[1];
		data->buf[data->config.win_height - y - 1][x] = data->config.cf_color[0];
		y++;
	}
}
