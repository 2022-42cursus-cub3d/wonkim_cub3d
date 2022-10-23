/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonkim <wonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 12:29:22 by wonkim            #+#    #+#             */
/*   Updated: 2022/10/23 14:00:56 by wonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/cub3d.h"

int	ft_endcmp(char *str, char *s)
{
	int size;
	int	i;

	size = ft_strlen(str) - 1;
	i = ft_strlen(s) - 1;
	while (i >= 0 && size >= 0)
	{
		if (str[size--] != s[i--])
			return (0);
	}
	return (1);
}

long long	ft_abs(int n)
{
	long long n2;

	n2 = n;
	if (n < 0)
		return (n2 * -1);
	return (n2);
}

int			ft_intlen(int n)
{
	int			len;
	long long	n2;

	len = 1;
	n2 = ft_abs(n);
	while (n2 /= 10)
		len++;
	return (len);
}

char		*ft_itoa(int n)
{
	char		*str;
	long long	n2;
	int			i;
	int			len;

	n2 = ft_abs(n);
	i = 1;
	len = ft_intlen(n);
	if (n < 0)
		len++;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (n < 0)
		str[0] = '-';
	while (i <= len)
	{
		if (str[len - i] != '-')
			str[len - i] = (n2 % 10) + '0';
		n2 /= 10;
		i++;
	}
	str[len] = '\0';
	return (str);
}

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
