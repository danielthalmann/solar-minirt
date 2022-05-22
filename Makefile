NAME=minirt

SRCS=	main.c \
		error.c \
		input.c \
		print_scene.c \
		parsing/parse.c \
		parsing/parse_ambiant.c \
		parsing/parse_light.c \
		parsing/parse_camera.c \
		parsing/parse_sphere.c \
		parsing/parse_plane.c \
		parsing/parse_cylinder.c \
		parsing/parse_check.c

OBJS=$(addprefix $(SRC_PATH), $(SRCS:.c=.o))

TESTS=	$(TEST_PATH)/main.c \
		$(TEST_PATH)/error.c \
		$(TEST_PATH)/parser.c \
		$(SRC_PATH)/parsing/parse.c \
		$(SRC_PATH)/parsing/parse_ambiant.c \
		$(SRC_PATH)/parsing/parse_light.c \
		$(SRC_PATH)/parsing/parse_camera.c \
		$(SRC_PATH)/parsing/parse_sphere.c \
		$(SRC_PATH)/parsing/parse_plane.c \
		$(SRC_PATH)/parsing/parse_cylinder.c \
		$(SRC_PATH)/parsing/parse_check.c

TEST_OBJS=$(TESTS:.c=.o)


CC=gcc

CFLAGS=-Wall -Werror -Wextra \
	   -I $(LIBFT_INCLUDE) \
	   -I $(GL_INCLUDE) \
	   -I $(MLX_INCLUDE) \
	   -I $(LIBFT_INCLUDE) \
	   -I ./srcs \
	   #-g -fsanitize=address -fno-omit-frame-pointer

# path

GL_LIB_PATH	 =./glmath/
GL_LIB		 = $(addprefix $(GL_LIB_PATH), lib)
GL_INCLUDE	 = $(addprefix $(GL_LIB_PATH), include)
GL_FLAG		 = glmath

LIBFT_PATH		 = ./libft
LIBFT_LIB	 	 = $(LIBFT_PATH)
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
	LDFLAGS = -lm -lz -lXext -lX11 #-g -fsanitize=address -fno-omit-frame-pointer

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
TEST_PATH	 =./tests/

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(GL_LIB_PATH)
	$(MAKE) -C $(MLX_LIB_PATH)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(OBJS) -l$(GL_FLAG) -l$(MLX_FLAG) -l$(LIBFT_FLAG) -L$(GL_LIB) -L$(MLX_LIB) -L$(LIBFT_LIB) $(LDFLAGS) -o $(NAME)

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
	./$(NAME) scenes/basic.rt

test: CFLAGS += -g 
test: $(TEST_OBJS) $(LIBFT)
	$(MAKE) -C $(GL_LIB_PATH)
	$(MAKE) -C $(MLX_LIB_PATH)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(TEST_OBJS) -l$(GL_FLAG) -l$(MLX_FLAG) -l$(LIBFT_FLAG) -L$(GL_LIB) -L$(MLX_LIB) -L$(LIBFT_LIB) $(LDFLAGS) -o test

norm: norminette

norminette:
	@norminette $(GL_LIB_PATH) $(SRC_PATH) $(TEST_PATH) $(INCLUDE_PATH) $(INCLUDE_PATH)

.PHONY: clean fclean norm norminette re run
