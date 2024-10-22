# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 12:33:33 by qsomarri          #+#    #+#              #
#    Updated: 2024/10/17 16:01:45 by qsomarri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = @cc

CFLAGS = -Wall -Wextra -Werror -g -I./includes

RM = @rm -rf

MAKE = @make -C

SRCS_DIR = srcs

SRCS =	$(SRCS_DIR)/free.c \
	$(SRCS_DIR)/initializer.c \
	$(SRCS_DIR)/main.c \
	$(SRCS_DIR)/monitor.c \
	$(SRCS_DIR)/output.c \
	$(SRCS_DIR)/philo_utils.c \
	$(SRCS_DIR)/routine.c \

OBJ_DIR = obj

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Cible principale
all:	$(NAME)

# Création de l'exécutable
$(NAME):	$(OBJS)
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJS)
		@echo "\033[0;92m * $(NAME) program file was created\033[0m *"

# Création du répertoire des objets
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Nettoyage des fichiers objets
clean:
	@$(RM) $(OBJ_DIR)
	@echo "\033[0;91m* $(NAME) object files was deleted *\033[0m"

# Nettoyage complet
fclean:	clean
	@$(RM) $(NAME)
	@echo "\033[0;91m* $(NAME) was deleted *\033[0m"

# Reconstruction complète
re: fclean all

.PHONY: all clean fclean re
