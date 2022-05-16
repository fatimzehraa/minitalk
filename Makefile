# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/12 16:57:44 by fael-bou          #+#    #+#              #
#    Updated: 2022/05/13 18:12:52 by fael-bou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

BUILD_DIR = build

CLIENT_OBJ = $(addprefix $(BUILD_DIR)/client/, client.o utils.o)
SERVER_OBJ = $(addprefix $(BUILD_DIR)/server/, server.o utils.o)

CLIENT_NAME = client
SERVER_NAME = server

all : $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME) : $(CLIENT_OBJ)
	$(CC) $^ -o $@

$(SERVER_NAME) : $(SERVER_OBJ)
	$(CC) $^ -o $@

$(BUILD_DIR)/%.o : src/%.c
	mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $< -o $@

clean :
	rm -rf $(BUILD_DIR)
fclean : clean
	rm -rf $(CLIENT_NAME) $(SERVER_NAME)

re : fclean all
