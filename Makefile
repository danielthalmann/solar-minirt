NAME=minirt

SRCS=	main.c \
		input.c
		# parsing/parse.c \
		# parsing/parse_utils.c \
		# parsing/parse_ambiant.c

OBJS=$(addprefix $(SRC_PATH), $(SRCS:.c=.o))

CC=gcc

CFLAGS=-Wall -Werror -Wextra \
	   -I $(INCLUDE_PATH) \
	   -I $(GL_INCLUDE) \
	   -I $(MLX_INCLUDE) \
	   -I $(LIBFT_INCLUDE) \
	   -g

# path

GL_LIB_PATH	 =./glmath/
GL_LIB		 = $(addprefix $(GL_LIB_PATH), lib)
GL_INCLUDE	 = $(addprefix $(GL_LIB_PATH), include)
GL_FLAG		 = glmath

LIBFT_PATH		 = ./libft
LIBFT			 = $(LIBFT_PATH)/libft.a
LIBFT_INCLUDE	 = $(LIBFT_PATH)/include
LIBFT_FLAG		 = ft

MLX_LIB_PATH = ./minilibx_linux/
MLX_LIB		 = $(MLX_LIB_PATH)
MLX_INCLUDE  = $(MLX_LIB_PATH)
MLX_FLAG	 = mlx

LDFLAGS = -lXext -lX11 -lz

# detection du systeme d'exploitation
UNAME_S := $(shell uname -s)
# pour linux
ifeq ($(UNAME_S),Linux)
	LDFLAGS = -lm -lz -lXext -lX11 -g

	MLX_LIB_PATH = ./minilibx_linux/
	MLX_LIB		 = $(MLX_LIB_PATH)
	MLX_INCLUDE  = $(MLX_LIB_PATH)
	MLX_FLAG	 = mlx

endif
# pour macOS
ifeq ($(UNAME_S),Darwin)

	LDFLAGS = -lm -lz -framework OpenGL -framework AppKit

	MLX_LIB_PATH = ./minilibx_opengl/
	MLX_LIB		 = $(MLX_LIB_PATH)
	MLX_INCLUDE  = $(MLX_LIB_PATH)
	MLX_FLAG	 = mlx

endif

GL			 = glmath
INCLUDE_PATH =./include/
SRC_PATH	 =./srcs/

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(MAKE) -C $(GL_LIB_PATH)
	$(MAKE) -C $(MLX_LIB_PATH)
	$(CC) $(OBJS) -l$(GL_FLAG) -l$(MLX_FLAG) $(LIBFT) -L$(GL_LIB) -L$(MLX_LIB) $(LDFLAGS) -o $(NAME)

$(LIBFT) :
	$(MAKE) -C $(LIBFT_PATH)

clean:
	$(MAKE) -C $(GL_LIB_PATH) clean
	$(MAKE) -C $(LIBFT_PATH) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(GL_LIB_PATH) fclean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

norminette:
	@norminette $(GL_LIB_PATH) $(SRC_PATH) $(INCLUDE_PATH)
