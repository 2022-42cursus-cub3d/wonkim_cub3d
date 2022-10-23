/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonkim <wonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:18:49 by wonkim            #+#    #+#             */
/*   Updated: 2022/10/23 14:32:32 by wonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/cub3d.h"

int		ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strrchr(char *s, int c)
{
	int	size;

	size = ft_strlen(s) + 1;
	while (size--)
	{
		if (s[size] == (char)c)
			return ((char*)(s + size));
	}
	return (NULL);
}

t_list	*lst_add_back(t_list **lst, char *line)
{
	t_list	*tail;
	t_list	*new;

	if (!line)
		return (0);
	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (0);
	new->content = line;
	new->next = NULL;
	if (!(*lst))
		*lst = new;
	else
	{
		tail = ft_lstlast(*lst);
		tail->next = new;
	}
	return (new);
}

int		lst_clear(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = *lst;
		free(tmp->content);
		*lst = (*lst)->next;
		free(tmp);
	}
	return (0);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int		is_space(char ch)
{
	if (ch == '\n' || ch == '\v' || ch == '\f'
			|| ch == '\r' || ch == '\t' || ch == ' ')
		return (1);
	return (0);
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_swap(int *n1, int *n2)
{
	int	tmp;

	tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;
}

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

char	*ft_strrchr(const char *str, int c)
{
	char			*s;
	char			*ret;
	unsigned char	find;
	int				flag;

	s = (char *)str;
	ret = 0;
	find = (unsigned char)c;
	flag = 1;
	while (*s)
	{
		if ((unsigned char)*s++ == find)
		{
			ret = s - 1;
			flag = 0;
		}
	}
	if ((unsigned char)*s == find && flag)
		return (s);
	return (ret);
}

void	buf_free(t_data *data, int i)
{
	while (i >= 0)
	{
		free(data->buf[i]);
		i--;
	}
	free(data->buf);
}

char	*ft_strdup(const char *s1)
{
	char	*s;
	char	*ret;
	int		i;

	s = (char *)s1;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!ret)
		return (0);
	i = -1;
	while (s[++i] != '\0')
		ret[i] = s[i];
	ret[i] = '\0';
	return (ret);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	idx;

	idx = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	ret[0] = '\0';
	if (ft_strlen(s) < start)
		return (ret);
	while (s[idx + start] != '\0' && idx < len)
	{
		ret[idx] = s[idx + start];
		idx++;
	}
	ret[idx] = '\0';
	return (ret);
}

void	clear_window(t_data *data)
{
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx, data->img.img_ptr);
	if (data->mlx && data->win)
		mlx_destroy_window(data->mlx, data->win);
}
