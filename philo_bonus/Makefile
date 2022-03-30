# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/12 14:53:45 by spoolpra          #+#    #+#              #
#    Updated: 2022/03/30 16:22:31 by spoolpra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

SRC_DIR = srcs/
OBJ_DIR = objs/

INCS = -Iincludes/ -I$(LIB_DIR)includes/
NAME = philo_bonus
SRCS = philo.c input.c time.c simulation.c init.c living.c routine.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR),$(OBJS))
	$(CC) $^ -o $(NAME) -lpthread
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< $(INCS) -o $@
clean:
	$(RM) $(OBJ_DIR)
fclean: clean
	$(RM) $(NAME)
re: fclean all
