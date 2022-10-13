/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonkim <wonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:06:07 by wonkim            #+#    #+#             */
/*   Updated: 2022/10/13 18:52:29 by wonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

int	main(int ac, char **av)
{
/*
	struct
*/
	t_data	data;

/*
check ac
*/
	if (ac != 2 || ft_strcmp(ft_strrchr(av[], '.'), ".cub"))
		return (error( ,"Error\n check argument\n"));
/*
data_calloc
*/
	data = ()ft_calloc();
	if (!data)
		return (error());
/*
initialize
*/
	data->mlx = mlx_init();
	if ((!parsing(data, &map, av)))
		return (error());
	mlx_mouse_move();
/*
set_handler
*/
	map
	player
	texture
/*
mlx
*/
	mlx_loop_hook(data.mlx_ptr, draw_game, &data);
	mlx_hook(data.mlx_win, 6, 0, mouse_hook, &data);
	mlx_hook(data.mlx_win, 2, 0, key_press, &data);
	mlx_hook(data.mlx_win, 3, 0, key_release, &data);
	mlx_hook(data.mlx_win, 17, 0, exit_game, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
