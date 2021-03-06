# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/12 12:30:52 by lsuardi           #+#    #+#              #
#    Updated: 2020/10/10 23:03:47 by lsuardi          ###   ########.fr        #
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
MAPDIR =	map

SRC =		main.c\
			get_next_line.c\
			get_next_line_utils.c\
			get_next_line_end.c\
			cub3d.c\
			error.c\
			get_set.c\
			get_set_utils.c\
			help.c\
			putstr.c\
			search_str.c\
			strcmp.c\
			strstr.c\
			strlen.c\
			c_is.c\
			strchr.c\
			atoi.c\
			get_file.c\
			clear.c\
			get_path.c\
			error_2.c\
			strdup.c\
			lst_line.c\
			str_is.c\
			get_map.c\
			get_map_from_list.c\
			get_map_utils.c\
			is_map_full_wall.c\
			rays.c\
			rays2.c\
			splist.c\
			memcpy.c\
			bzero.c\
			save_screen.c\
			save_screen2.c\
			inittextures.c\
			keyhandling.c\
			keyhandlingutils.c\
			drawsprites.c
OBJ =		$(SRC:.c=.o)
LIB =		libmlx.a
SCRIPT =	ext.sh\
			fclean.sh

CFLAGS =	-Wall -Wextra -Werror -I $(INCDIR)
CFLAGS_2 =	

GRN =		\x1b[32m
RED =		\x1b[31m
L_RED =		\x1b[91m
L_GRN =		\x1b[92m
BLU =		\x1b[34m
BLD =		\x1b[1m
NRM =		\x1b[0m

ifeq ("$(OS)", "Darwin")
	CFLAGS_2 =	-L lib -lmlx -framework OpenGL -framework AppKit -lbsd -lm
endif

ifeq ("$(OS)", "Linux")
	CFLAGS_2 =	-L lib -lmlx -lXext -lX11 -lbsd -lm
	GRN =		\e[32m
	RED =		\e[31m
	L_RED =		\e[91m
	L_GRN =		\e[92m
	BLU =		\e[34m
	BLD =		\e[1m
	NRM =		\e[0m
endif

all: $(addprefix $(SHDIR)/, $(SCRIPT)) $(MAPDIR) $(addprefix $(LIBDIR)/, $(LIB)) $(NAME)
	@(sh $(SHDIR)/help.sh .; echo '$(GRN)$(BLD)$(NAME)$(NRM)$(GRN) is up to date.$(NRM)')

bonus: all

$(addprefix $(LIBDIR)/, $(LIB)): $(addprefix $(EXTDIR)/, $(EXT))
	@(sh $(SHDIR)/ext.sh .)

$(NAME): $(addprefix $(OBJDIR)/, $(OBJ))
	@(echo '\n$(BLU)Compiling [$(BLD)$@$(NRM)$(BLU)] ...$(NRM)'; gcc $(CFLAGS) $^ $(CFLAGS_2) -o $@)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(addprefix $(INCDIR)/, $(INC)) | $(OBJDIR)
	@(printf '\r$(BLU)Compiling'; gcc $(CFLAGS) -c $< -o $@; printf ' [ $(BLD)'; ls $(OBJDIR) | wc -w | tr -d ' \n'; printf ' $(NRM)$(BLU)/ $(BLD)'; echo $(SRC) | wc -w | tr -d ' \n'; printf ' $(NRM)$(BLU)]$(NRM)')

$(OBJDIR):
	@(mkdir $(OBJDIR))

$(MAPDIR):
	@(mkdir $(MAPDIR))

m: all
	@(sh $(SHDIR)/map.sh .; sh $(SHDIR)/assets.sh)

clean:
	@(rm -rf $(OBJDIR); echo '$(RED)Removed [$(BLD)$(RED)$(OBJDIR)$(NRM)$(RED)]$(NRM)')

fclean: clean
	@(sh $(SHDIR)/fclean.sh .)

re: fclean all
