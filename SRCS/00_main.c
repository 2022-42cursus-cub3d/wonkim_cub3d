/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonkim <wonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 12:18:29 by wonkim            #+#    #+#             */
/*   Updated: 2022/10/23 14:11:00 by wonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	ptr_init(&data);
	if (ac != 2 || ft_strcmp(ft_strrchr(av[1], '.'), ".cub"))
		return ((error(&data, "error", -1)));
	if (!parse_config(&data.config, av[1]))
		return (error(&data, "parsing error", -1));
	if (!(data_init(&data) == -1) || window_init(&data) == -1)
		return (error(&data, "malloc error", 1));
	load_texture(&data);
	screen_size(data.mlx_ptr, &data.config->win_width, &data.config->win_height);
	mlx_loop_hook(data.mlx_ptr, start_game, &data);
	mlx_hook(data.mlx_win, 2, 0, key_press, &data);
	mlx_hook(data.mlx_win, 3, 0, key_release, &data);
	mlx_hook(data.mlx_win, 17, 0, game_close, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
