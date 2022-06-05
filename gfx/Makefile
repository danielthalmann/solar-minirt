NAME=libgfx.a

SRCS=	init.c \
		window.c \
		image.c \

OBJS=$(addprefix $(SRC_PATH), $(SRCS:.c=.o))

CC=gcc

CFLAGS=-Wall -Werror -Wextra -I $(INCLUDE_PATH)

# detection du systeme d'exploitation
UNAME_S := $(shell uname -s)
# pour linux
ifeq ($(UNAME_S),Linux)
	CFLAGS += -lm
endif

# path
LIB_PATH=./lib/
LIB=$(LIB_PATH)$(NAME)
INCLUDE_PATH=./include/
SRC_PATH=./srcs/

# pour linux
ifeq ($(UNAME_S),Linux)
	LDFLAGS = -lm -lz -lXext -lX11 \
			  # -g -fsanitize=address -fno-omit-frame-pointer

	MLX_LIB_PATH = ../minilibx_linux/
	MLX_LIB		 = $(MLX_LIB_PATH)/libmlx.a
	MLX_INCLUDE  = $(MLX_LIB_PATH)
	MLX_FLAG	 = mlx

# pour macOS
else ifeq ($(UNAME_S),Darwin)
	LDFLAGS = -lm -lz -framework OpenGL -framework AppKit
	MLX_LIB_PATH = ../minilibx_opengl/
	MLX_LIB		 = $(MLX_LIB_PATH)/libmlx.a
	MLX_INCLUDE  = $(MLX_LIB_PATH)
	MLX_FLAG	 = mlx
endif
CFLAGS += -I$(MLX_INCLUDE)

$(LIB): $(OBJS)
	ar rcs $(addprefix $(LIB_PATH), $(NAME)) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(addprefix $(LIB_PATH), $(NAME))

re: fclean $(NAME)
