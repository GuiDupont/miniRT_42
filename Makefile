# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/16 11:20:55 by gdupont           #+#    #+#              #
#    Updated: 2020/06/19 12:43:54 by gdupont          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CC = gcc

FLAGS = -Wall -Wextra -Werror

PATH_SRCS = srcs

MINILIBX = minilibx

LIBFT = libft

SRCS_LIST		= \
				maths/quaternion_operations.c \
				maths/vector_operations_2.c \
				maths/vector_operations.c \
				\
				parsing/check_valid_2.c parsing/check_valid_tools_2.c parsing/init_data.c \
				parsing/set_up_light.c parsing/set_up_sp.c parsing/check_valid_3.c \
				parsing/check_valid_tools.c parsing/set_up_c.c parsing/set_up_plane.c \
				parsing/set_up_square.c parsing/check_valid.c parsing/file_to_scene.c \
				parsing/set_up_cy.c parsing/set_up_res_a.c parsing/set_up_tr.c \
				\
				program_management/error_and_exit.c program_management/free_elem.c \
				program_management/launch_program.c program_management/manage_event_2.c \
				program_management/manage_event_3.c program_management/manage_event.c \
				program_management/scene_to_bmp.c \
				\
				raytracing/intersection_prim_2.c raytracing/intersection_prim.c raytracing/ray_op.c \
				raytracing/ray_tracing.c raytracing/scene_to_image.c raytracing/transform_prim.c \

SRCS = $(addprefix ${PATH_SRCS}/, ${SRCS_LIST})

OBJS = $(SRCS:.c=.o)

INCLUDES = -I./includes

SGFLAGS = -g -fsanitize=address

all : $(NAME)

$(NAME) :	$(OBJS)
	@make -C $(MINILIBX) all
	@make -C $(LIBFT) all
	@$(CC) $(FLAGS) $(SGFLAGS) $(INCLUDES) $(OBJS) minilibx/*.a -L -lmlx -lX11 -lXext -lm libft/libft.a -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< $(INCLUDES) -o $@

clean:
	@rm -f $(OBJS)
	@make clean -s -C $(MINILIBX)
	@make clean -s -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -s -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re bonus
