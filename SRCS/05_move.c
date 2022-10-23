/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonkim <wonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:06:44 by wonkim            #+#    #+#             */
/*   Updated: 2022/10/23 12:18:02 by wonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/cub3d.h"

void	move_vertical(t_data *data, int direction)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = data->pos_x + direction * data->dir_x * data->move_speed;
	tmp_y = data->pos_y + direction * data->dir_y * data->move_speed;
	if (direction == 1)
	{
		if (data->config->map[tmp_x][tmp_y] != '1')
		{
			data->pos_x += data->dir_x * data->move_speed;
			data->pos_y += data->dir_y * data->move_speed;
		}
	}
	if (direction == -1)
	{
		if (data->config->map[tmp_x][tmp_y] != '1')
		{
			data->pos_x -= data->dir_x * data->move_speed;
			data->pos_y -= data->dir_y * data->move_speed;
		}
	}
}

void	move_horizontal(t_data *data, int direction)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = data->pos_x + direction * data->pln_x * data->move_speed;
	tmp_y = data->pos_y + direction * data->pln_y * data->move_speed;
	if (direction == 1)
	{
		if (data->config->map[tmp_x][tmp_y] != '1')
		{
			data->pos_x += data->pln_x * data->move_speed;
			data->pos_y += data->pln_y * data->move_speed;
		}
	}
	if (direction == -1)
	{
		if (data->config->map[tmp_x][tmp_y] != '1')
		{
			data->pos_x -= data->pln_x * data->move_speed;
			data->pos_y -= data->pln_y * data->move_speed;
		}
	}
}

void	rotate(t_data *data, int direction)
{
	double	old_dir_x;
	double	old_pln_x;
	double	tmp_x;
	double	tmp_y;

	old_dir_x = data->dir_x;
	tmp_x = data->dir_x * cos(direction * data->rotation_speed);
	tmp_y = data->dir_y * sin(direction * data->rotation_speed);
	data->dir_x = tmp_x - tmp_y;
	tmp_x = old_dir_x * sin(direction * data->rotation_speed);
	tmp_y = data->dir_y * cos(direction * data->rotation_speed);
	data->dir_y = tmp_x + tmp_y;
	old_pln_x = data->pln_x;
	tmp_x = data->pln_x * cos(direction * data->rotation_speed);
	tmp_y = data->pln_y * sin(direction * data->rotation_speed);
	data->pln_x = tmp_x - tmp_y;
	tmp_x = old_pln_x * sin(direction * data->rotation_speed);
	tmp_y = data->pln_y * cos(direction * data->rotation_speed);
	data->pln_y = tmp_x + tmp_y;
}
