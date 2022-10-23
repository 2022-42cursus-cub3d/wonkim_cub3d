/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonkim <wonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 12:18:44 by wonkim            #+#    #+#             */
/*   Updated: 2022/10/23 14:30:10 by wonkim           ###   ########.fr       */
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

int		parse_map(t_config *config, t_list *map_buffer)
{
	int	i;

	if (!(config->map_row = check_map_row(map_buffer)))
		return (0);
	if (!(config->map_col = check_map_col(map_buffer)))
		return (0);
	if (!(config->map_c = malloc(sizeof(char*) * (config->map_row))))
		return (0);
	i = -1;
	while (++i < config->map_row)
		if (!(config->map_c[i] = malloc(sizeof(char)
		* (config->map_col))))
			return (-1);
	if (!copy_map(config, map_buffer) || !element_check(config->set))
		return (0);
	return (valid_map_check(config));
}
int			parse_resolution(t_config *config, char *line)
{
	int		i;

	i = 1;
	config->set[C_R] = 1;
	if (line && line[0] == 'R')
	{
		i = notspace_index(line, i);
		if (ft_strlen(line + i) == 0)
			return (0);
		if (ft_isdigit(line[i]))
			config->win_width = ft_atoi(line + i);
		while (line[i] && ft_isdigit(line[i]))
			i++;
		i = notspace_index(line, i);
		if (ft_isdigit(line[i]))
			config->win_height = ft_atoi(line + i);
		while (line[i] && ft_isdigit(line[i]))
			i++;
		i = notspace_index(line, i);
		if (line[i] != 0 || config->win_height < 0 || config->win_width < 0)
			return (0);
		return (1);
	}
	return (0);
}

int			parse_texture(t_config *config, int id, char *line)
{
	int		i;
	int		len;
	char	*path;

	i = 2;
	config->set[id] = 1;
	line += notspace_index(line, i);
	if (ft_strlen(line) == 0)
		return (0);
	if (config->tex_path[id])
	{
		free(config->tex_path[id]);
		config->tex_path[id] = 0;
	}
	len = ft_strlen(line) - 1;
	while (line[len] == ' ')
		len--;
	i = 0;
	while (i < len + 1)
		if (is_space(line[i++]))
			return (0);
	if (!(path = ft_substr(line, 0, len + 1)))
		return (0);
	config->tex_path[id] = path;
	return (1);
}

static int	color_split(char *line)
{
	int i;
	int cnt;
	int	len;

	len = ft_strlen(line);
	cnt = 0;
	while (is_space(line[--len]))
		line[len] = 0;
	i = 0;
	while (i < len + 1)
	{
		if (line[i] == ',')
			cnt++;
		if (line[i] != ',' && !ft_isdigit(line[i]))
			return (0);
		i++;
	}
	if (cnt == 2)
		return (1);
	return (0);
}

int			str_to_color(char *line)
{
	int rgb;
	int i;
	int cnt;
	int num;

	i = 0;
	cnt = 0;
	rgb = 0;
	if (!color_split(line))
		return (-1);
	while (line[i] != ',' && line[i] && cnt <= 16)
	{
		num = ft_atoi(line + i);
		if (num > 255 || num < 0)
			return (-1);
		rgb = (rgb | (num << (16 - cnt)));
		cnt += 8;
		i = notspace_index(line, i);
		while (line[i] && ft_isdigit(line[i]))
			i++;
		if (line[i] == ',')
			i++;
	}
	return (rgb);
}

int			parse_color(t_config *config, int id, char *line)
{
	int				i;
	unsigned int	color;

	i = notspace_index(line, 1);
	if (ft_strlen(line + i) == 0)
		return (0);
	if (!ft_isdigit(line[i]))
		return (0);
	if ((int)(color = str_to_color(line + i)) < 0)
		return (0);
	config->cf_color[id - T_C] = color;
	config->set[id] = 1;
	return (1);
}

int		check_map_row(t_list *map_buffer)
{
	int row;

	row = 0;
	while (map_buffer)
	{
		map_buffer = map_buffer->next;
		row++;
	}
	return (row);
}

int		check_map_col(t_list *map_buffer)
{
	int col;
	int max_col;

	max_col = 0;
	while (map_buffer)
	{
		col = ft_strlen(map_buffer->content) - 1;
		while (map_buffer->content[col] == ' ')
			col--;
		map_buffer->content[col + 1] = 0;
		if (max_col < col + 1)
			max_col = col + 1;
		map_buffer = map_buffer->next;
	}
	return (max_col);
}

int				check_map(t_config *config, int r, int c, int dir[2][4])
{
	int i;

	i = -1;
	if (r < 0 || c < 0 || r >= config->map_row || c >= config->map_col)
		return (0);
	if (config->map_c[r][c] == 0 || config->map_c[r][c] == ' ')
		return (0);
	if (config->map_c[r][c] == '1' || config->map_c[r][c] == 'x')
		return (1);
	config->map_c[r][c] = 'x';
	while (++i < 4)
		if (!check_map(config, r + dir[0][i], c + dir[1][i], dir))
			return (0);
	return (1);
}

static int		valid_char_map(t_config *config)
{
	int r;
	int c;

	r = -1;
	while (++r < config->map_row)
	{
		c = -1;
		while (++c < config->map_col)
			if (!ft_strrchr(" 012", config->map_c[r][c]))
				return (0);
	}
	return (1);
}

static int		map_init(int dir[2][4])
{
	int r;

	r = -1;
	dir[0][0] = 0;
	dir[0][1] = 0;
	dir[0][2] = 1;
	dir[0][3] = -1;
	while (++r < 4)
		dir[1][3 - r] = dir[0][r];
	return (1);
}
int				valid_map_check(t_config *config)
{
	int		r;
	int		c;
	int		is_valid;
	int		dir[2][4];

	is_valid = 0;
	if (!valid_char_map(config) || config->map_row <= 2 || config->map_col <= 2
	|| !map_init(dir) || !rotate_map(config))
		return (0);
	r = -1;
	while (++r < config->map_row)
	{
		c = -1;
		while (++c < config->map_col)
			if (config->map_c[r][c] == '0')
			{
				is_valid = 1;
				if (check_map(config, r, c, dir) == 0)
					return (0);
			}
	}
	return (is_valid && player_valid_check(config));
}


int		element_check(int set[])
{
	int i;

	i = -1;
	while (++i < 9)
		if (set[i] == 0 && i != C_MAP)
			return (0);
	return (1);
}

int		rotate_map(t_config *config)
{
	int		i;
	int		j;

	i = -1;
	if (!(config->map = malloc(sizeof(char*) * config->map_col)))
		return (0);
	while (++i < config->map_col)
		if (!(config->map[i] = malloc(sizeof(char) * config->map_row)))
			return (0);
	i = -1;
	while (++i < config->map_row)
	{
		j = -1;
		while (++j < config->map_col)
			config->map[j][i] = config->map_c[i][j];
	}
	return (1);
}

int		player_valid_check(t_config *config)
{
	int		r;
	int		c;

	r = config->pos_y;
	c = config->pos_x;
	if (r <= 0 || r >= config->map_row - 1
	|| c <= 0 || c >= config->map_col - 1)
		return (0);
	if (!ft_strrchr("1x", config->map_c[r][c + 1])
	|| !ft_strrchr("1x", config->map_c[r][c - 1])
	|| !ft_strrchr("1x", config->map_c[r + 1][c])
	|| !ft_strrchr("1x", config->map_c[r - 1][c]))
		return (0);
	return (1);
}

int		notspace_index(char *line, int ind)
{
	while (line[ind] && line[ind] == ' ')
		ind++;
	return (ind);
}

int		copy_map(t_config *config, t_list *map_buffer)
{
	int		i;
	int		j;

	i = -1;
	while (++i < config->map_row)
	{
		j = -1;
		while (++j < config->map_col)
		{
			if (!(map_buffer->content[j]))
			{
				while (j < config->map_col)
					config->map_c[i][j++] = ' ';
				break ;
			}
			config->map_c[i][j] = map_buffer->content[j];
			if (ft_strrchr("NSWE", config->map_c[i][j]))
				if (!player_set(config, j, i))
					return (0);
		}
		map_buffer = map_buffer->next;
	}
	return (1);
}

int		player_set(t_config *config, int x, int y)
{
	if (config->pos_x > 0 && config->pos_y > 0)
		return (0);
	config->pos_x = x;
	config->pos_y = y;
	config->dir = config->map_c[y][x];
	config->map_c[y][x] = '0';
	return (1);
}
