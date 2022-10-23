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

static int	ft_isblank(char c)
{
	if (c == ' ' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f' || c == '\t')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	char		*s;
	long long	ret;
	long long	flag;

	s = (char *)str;
	ret = 0;
	flag = 1;
	while (ft_isblank(*s))
		s++;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			flag *= -1;
	while (ft_isdigit(*s))
	{
		ret = ret * 10 + *s - '0';
		if (ret < 0)
		{
			if (flag < 0)
				return (0);
			else
				return (-1);
		}
		s++;
	}
	return (ret * flag);
}
