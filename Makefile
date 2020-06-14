# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/12 12:30:52 by lsuardi           #+#    #+#              #
#    Updated: 2020/06/13 14:57:50 by lsuardi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		Cub3D
OS =		$(shell uname)

SRCDIR =	src
OBJDIR =	obj
INCDIR =	inc
LIBDIR =	lib
EXTDIR =	ext
SHDIR =		script

SRC =		main.c
OBJ =		$(SRC:.c=.o)
LIB =		libmlx.a
SCRIPT =	ext.sh\
			fclean.sh

CFLAGS =	-Wall -Wextra -Werror -I $(INCDIR)

GRN =		\x1b[32m
RED =		\x1b[31m
L_RED =		\x1b[91m
L_GRN =		\x1b[92m
BLU =		\x1b[34m
BLD =		\x1b[1m
NRM =		\x1b[0m

ifeq ("$(OS)", "Darwin")
	CFLAGS +=	-L lib -lmlx -framework OpenGL -framework AppKit
else
ifeq ("$(OS)", "Linux")
	CFLAGS +=	-lmlx -lXext -lX11
	GRN =		\e[32m
	RED =		\e[31m
	L_RED =		\e[91m
	L_GRN =		\e[92m
	BLU =		\e[34m
	BLD =		\e[1m
	NRM =		\e[0m
endif
endif

all: $(addprefix $(SHDIR)/, $(SCRIPT)) $(addprefix $(LIBDIR)/, $(LIB)) $(NAME)

$(addprefix $(LIBDIR)/, $(LIB)): $(addprefix $(EXTDIR)/, $(EXT))
	@(sh $(SHDIR)/ext.sh .)

$(NAME): $(OBJDIR) $(addprefix $(OBJDIR)/, $(OBJ))
	@(echo '\n$(BLU)Compiling [$(BLD)$@$(NRM)$(BLU)] ...$(NRM)'; gcc $(CFLAGS) $(CFLAGS_2) $^ -o $(NAME))

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(addprefix $(INCDIR)/, $(INC))
	@(printf '\r$(BLU)Compiling'; gcc $(CFLAGS) -c $< -o $@; printf ' [ $(BLD)'; ls $(OBJDIR) | wc -w | tr -d ' \n'; printf ' $(NRM)$(BLU)/ $(BLD)'; printf $(SRC) | wc -w | tr -d ' \n'; printf ' $(NRM)$(BLU))$(NRM)')

$(OBJDIR):
	@(mkdir $(OBJDIR))

clean:
	@(rm -rf $(OBJDIR); echo '$(RED)Removed [$(BLD)$(RED)$(OBJDIR)$(NRM)$(RED)]$(NRM)')

fclean: clean
	@(sh $(SHDIR)/fclean.sh .)

re: fclean all
