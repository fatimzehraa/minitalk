# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/12 16:57:44 by fael-bou          #+#    #+#              #
#    Updated: 2022/05/16 19:51:43 by fael-bou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

BUILD_DIR = build

CLIENT_OBJ = $(addprefix $(BUILD_DIR)/client/, client.o)
SERVER_OBJ = $(addprefix $(BUILD_DIR)/server/, server.o)

CLIENT_BONUS_OBJ = $(addprefix $(BUILD_DIR)/client/, client_bonus.o)
SERVER_BONUS_OBJ = $(addprefix $(BUILD_DIR)/server/, server_bonus.o)

CLIENT_NAME = client
SERVER_NAME = server

CLIENT_BONUS_NAME = client_bonus
SERVER_BONUS_NAME = server_bonus

all : $(CLIENT_NAME) $(SERVER_NAME)

bonus : $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME)

$(CLIENT_NAME) : $(CLIENT_OBJ)
	$(CC) $^ -o $@

$(SERVER_NAME) : $(SERVER_OBJ)
	$(CC) $^ -o $@

$(CLIENT_BONUS_NAME) : $(CLIENT_BONUS_OBJ)
	$(CC) $^ -o $@

$(SERVER_BONUS_NAME) : $(SERVER_BONUS_OBJ)
	$(CC) $^ -o $@

$(BUILD_DIR)/%.o : src/%.c
	mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $< -o $@

clean :
	rm -rf $(BUILD_DIR)
fclean : clean
	rm -f $(CLIENT_NAME) $(SERVER_NAME) $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME)

re : fclean all
