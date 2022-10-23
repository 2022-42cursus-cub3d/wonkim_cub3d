



#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

typedef struct		s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

/*
** texture.c
*/

void	screen_size(void *mlx, int *width, int *height);
int		ft_atoi(const char *str);

/*
** key_handling.c
*/

int			ft_endcmp(char *str, char *s);
long long	ft_abs(int n);
int			ft_intlen(int n);
char		*ft_itoa(int n);
int			ft_strcmp(char *s1, char *s2);
int			ft_strlen(char *s);
char		*ft_strrchr(char *s, int c);
t_list		*lst_add_back(t_list **lst, char *line);
int			lst_clear(t_list **lst);
t_list		*ft_lstlast(t_list *lst);
int			is_space(char ch);
int			ft_isdigit(int c);
void		ft_swap(int *n1, int *n2);
void		screen_size(void *mlx, int *width, int *height);

#endif
