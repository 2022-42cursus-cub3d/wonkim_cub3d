/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonkim <wonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:15:18 by wonkim            #+#    #+#             */
/*   Updated: 2022/10/17 17:25:04 by wonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/cub3d.h"

int		key_update(t_data *data)
{
	if (data->key.w)
		move_vertical(data, 1);
	if (data->key.s)
		move_vertical(data, -1);
	if (data->key.a)
		move_horizontal(data, -1);
	if (data->key.d)
		move_horizontal(data, 1);
	if (data->key.right)
		rotate(data, 1);
	if (data->key.left)
		rotate(data, -1);
	return (0);
}

int		key_press(int key, t_data *data)
{
	if (key == KEY_W)
		data->key.w = 1;
	else if (key == KEY_S)
		data->key.s = 1;
	if (key == KEY_A)
		data->key.a = 1;
	else if (key == KEY_D)
		data->key.d = 1;
	if (key == KEY_LEFT)
		data->key.left = 1;
	if (key == KEY_RIGHT)
		data->key.right = 1;
	if (key == KEY_ESC)
		main_close(data);
	return (0);
}

int		key_release(int key, t_data *data)
{
	if (key == KEY_W)
		data->key.w = 0;
	else if (key == KEY_S)
		data->key.s = 0;
	else if (key == KEY_A)
		data->key.a = 0;
	else if (key == KEY_D)
		data->key.d = 0;
	else if (key == KEY_LEFT)
		data->key.left = 0;
	else if (key == KEY_RIGHT)
		data->key.right = 0;
	return (0);
}
