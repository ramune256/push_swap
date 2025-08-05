# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/18 21:38:29 by shunwata          #+#    #+#              #
#    Updated: 2025/08/05 19:46:36 by shunwata         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INC_DIR) -I $(LIBFT_DIR)/includes -I $(FT_PRINTF_DIR) -I $(GET_NEXT_LINE_DIR)

SRC_DIR = srcs
INC_DIR = includes

SRC = $(addprefix $(SRC_DIR)/, error_finder.c main.c node_management.c operations1.c operations2.c operations3.c parse_args.c sort.c stack_management.c)
OBJ = $(SRC:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DIR = Libft

FT_PRINTF_DIR = $(LIBFT_DIR)/srcs/ft_printf
GET_NEXT_LINE_DIR = $(LIBFT_DIR)/srcs/get_next_line

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
