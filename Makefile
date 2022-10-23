# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/23 12:20:44 by wonkim            #+#    #+#              #
#    Updated: 2022/10/23 14:24:13 by hyojlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

INC_PATH	= ./INC
SRC_PATH	= ./SRCS
MLX_PATH	= ./MLX
MMS_PATH	= ./MLX_BETA
GNL_PATH	= ./LIBFT_GNL/get_next_line

INCS		= -I$(INC_PATH)
SRCS		= $(SRC_PATH)/00_main.c \
				$(SRC_PATH)/01_initialize.c \
				$(SRC_PATH)/02_parsing.c \
				$(SRC_PATH)/03_draw.c \
			 	$(SRC_PATH)/04_keypress.c \
			 	$(SRC_PATH)/05_move.c \
			  	$(SRC_PATH)/06_textures.c \
				$(SRC_PATH)/07_utils1.c \
				$(SRC_PATH)/08_utils2.c \
				$(GNL_PATH)/get_next_line.c \
			  	$(GNL_PATH)/get_next_line_utils.c
OBJS		= 	$(SRCS:.c=.o)

CC			= cc
CFLAGS		= -O3 -Wall -Wextra -Werror
MLXFLAGS	= -Lmlx -lm -Lmlx_beta -lmlx -framework OpenGL -framework AppKit
MMS			= libmlx.dylib
MLX			= libm.a

.c.o:
		$(CC) $(CFLAGS) $(INCS) -c $< -o $(<:.c=.o)

$(NAME): $(MLX) $(OBJS) $(MMS)
		$(CC) $(CFLAGS) $(INCS) -o $(NAME) -L $(MLX_PATH) $(MLXFLAGS) $(OBJS)
		@echo $(NAME) : Created

$(MLX):
		@$(MAKE) -C mlx
		mv $(MLX_PATH)/libmlx.a $(MLX_PATH)/$(MLX)

$(MMS):
		@$(MAKE) -C mlx_beta
		cp $(MMS_PATH)/$(MMS) .

all:	$(NAME)

clean:
		@$(MAKE) -C mlx clean
		@$(MAKE) -C mlx_beta clean
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME) $(BONUS) $(MMS) $(MLX_PATH)/$(MLX)

re:
		make fclean
		make all

.PHONY: all clean fclean re
