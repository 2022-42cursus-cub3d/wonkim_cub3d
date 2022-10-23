/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonkim <wonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 12:18:44 by wonkim            #+#    #+#             */
/*   Updated: 2022/10/23 12:18:45 by wonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../INC/cub3d.h"

int		parse_config(t_config *config, char *path)
{
	int		fd;
	char	*line;
	t_list	*map_buffer;
	int		r;

	config_init(config);
	if ((fd = open(path, O_RDONLY)) < 0)
		return (0);
	map_buffer = 0;
	r = 1;
	while (get_next_line(fd, &line))
	{
		r = (r && parse_line(config, line, &map_buffer));
		free(line);
	}
	if (r && ft_strlen(line) > 0)
		r = (r && parse_line(config, line, &map_buffer));
	free(line);
	close(fd);
	if (!r || !parse_map(config, map_buffer))
		return (lst_clear(&map_buffer));
	lst_clear(&map_buffer);
	ft_swap(&config->map_col, &config->map_row);
	return (1);
}

void	config_init(t_config *config)
{
	int	i;

	i = 0;
	config->win_height = -1;
	config->win_width = -1;
	while (i < TEXTURES)
		config->tex_path[i++] = 0;
	config->map_c = 0;
	config->map = 0;
	i = 0;
	while (i < 9)
		config->set[i++] = 0;
	config->pos_x = 0;
	config->pos_y = 0;
	config->map_row = 0;
	config->map_col = 0;
}

int		parse_line(t_config *config, char *line, t_list **map_buffer)
{
	static int	empty_map = 0;
	int			id;
	int			len;

	len = ft_strlen(line);
	if (len == 0 && config->set[C_MAP])
		empty_map = 1;
	if (len == 0)
		return (1);
	id = identifier(line);
	if (id != C_MAP && (config->set[C_MAP] || config->set[id]))
		return (0);
	if (id == C_R)
		return (parse_resolution(config, line));
	else if (id >= C_NO && id <= C_EA)
		return (parse_texture(config, id, line));
	else if (id == C_F || id == C_C)
		return (parse_color(config, id, line));
	config->set[id] = 1;
	if (empty_map)
		return (0);
	return (!!lst_add_back(map_buffer, ft_strdup(line)));
}

int		identifier(char *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (C_R);
	else if (line[0] == 'N' && line[1] == 'O')
		return (C_NO);
	else if (line[0] == 'S' && line[1] == 'O')
		return (C_SO);
	else if (line[0] == 'W' && line[1] == 'E')
		return (C_WE);
	else if (line[0] == 'E' && line[1] == 'A')
		return (C_EA);
	else if (line[0] == 'F' && line[1] == ' ')
		return (C_F);
	else if (line[0] == 'C' && line[1] == ' ')
		return (C_C);
	else
		return (C_MAP);
}

int		clear_config(t_config *config, int status)
{
	int i;

	i = -1;
	if (status < 0)
		ft_swap(&config->map_row, &config->map_col);
	else if (status == 0)
		return (1);
	while (++i < TEXTURES)
		if (config->tex_path[i] != 0)
			free(config->tex_path[i]);
	i = -1;
	while (config->map_c != 0 && ++i < config->map_col)
		if (config->map_c[i])
			free(config->map_c[i]);
	if (config->map_c != 0)
		free(config->map_c);
	i = -1;
	while (config->map != 0 && ++i < config->map_row)
		if (config->map[i])
			free(config->map[i]);
	if (config->map != 0)
		free(config->map);
	return (1);
}
