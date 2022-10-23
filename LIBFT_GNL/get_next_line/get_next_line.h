/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonkim <wonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:54:01 by sunhkim           #+#    #+#             */
/*   Updated: 2022/10/24 00:54:33 by wonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "../UTILS/utils.h"

# define BUFFER_SIZE 128

int				get_next_line(int fd, char **line);
char			*ft_substr(char *str, int start, int len);
int				save_line(char **dest, char *src, char **save);

char			*ft_strdup(char *s1);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, char *src, size_t dstsize);
char			*ft_strjoin(char *s1, char *s2);
int				ft_findchar(char *s);

#endif
