NAME=minirt

SRCS=	main.c \
		error.c \
		input.c \
		export_ppm.c \
		print_scene.c \
		parsing/parse.c \
		parsing/parse_ambient.c \
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
		$(SRC_PATH)/parsing/parse_ambient.c \
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
	   -I ./include \
	   # -g -fsanitize=address -fno-omit-frame-pointer

GL_LIB_PATH	 =./glmath/
GL_LIB		 = $(GL_LIB_PATH)/lib/libglmath.a
GL_INCLUDE	 = $(addprefix $(GL_LIB_PATH), include)

LIBFT_PATH		 = ./libft
LIBFT_LIB	 	 = $(LIBFT_PATH)/libft.a
LIBFT_INCLUDE	 = $(LIBFT_PATH)/include

MLX_LIB_PATH = ./minilibx_linux/
MLX_LIB		 = $(MLX_LIB_PATH)
MLX_INCLUDE  = $(MLX_LIB_PATH)

# detection du systeme d'exploitation
UNAME_S := $(shell uname -s)

# pour linux
ifeq ($(UNAME_S),Linux)
	LDFLAGS = -lm -lz -lXext -lX11 \
			  # -g -fsanitize=address -fno-omit-frame-pointer

	MLX_LIB_PATH = ./minilibx_linux/
	MLX_LIB		 = $(MLX_LIB_PATH)/libmlx.a
	MLX_INCLUDE  = $(MLX_LIB_PATH)
	MLX_FLAG	 = mlx

# pour macOS
else ifeq ($(UNAME_S),Darwin)
	LDFLAGS = -lm -lz -framework OpenGL -framework AppKit
	MLX_LIB_PATH = ./minilibx_opengl/
	MLX_LIB		 = $(MLX_LIB_PATH)/libmlx.a
	MLX_INCLUDE  = $(MLX_LIB_PATH)
	MLX_FLAG	 = mlx
endif

GL			 = glmath
INCLUDE_PATH =./include/
SRC_PATH	 =./srcs/
TEST_PATH	 =./tests/

all: compile

compile:
	@$(MAKE) -C $(LIBFT_PATH)
	@$(MAKE) -C $(GL_LIB_PATH)
	@$(MAKE) -C $(MLX_LIB_PATH)
	@$(MAKE) $(NAME)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_PATH)

$(GL_LIB):
	@$(MAKE) -C $(GL_LIB_PATH)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_LIB_PATH)

$(NAME): $(OBJS) $(LIBFT_LIB) $(GL_LIB) $(MLX_LIB)
	$(CC) $^ $(LDFLAGS) -o $(NAME)

clean:
	$(MAKE) -C $(GL_LIB_PATH) clean
	@#$(MAKE) -C $(MLX_LIB_PATH) clean
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
test: $(TEST_OBJS) compile
	$(CC) $(TEST_OBJS) $(LIBFT_LIB) $(GL_LIB) $(MLX_LIB) $(LDFLAGS) -o test

norm: norminette

norminette:
	@norminette $(GL_LIB_PATH) $(SRC_PATH) $(TEST_PATH) $(INCLUDE_PATH)

.PHONY: clean fclean norm norminette re run compile
