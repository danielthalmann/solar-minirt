NAME=libglmath.a

SRCS=	scene.c \
		vector.c \
		vector_norm.c \
		vector_add_sub.c \
		vector_angle_op.c \
		vector_scalar_op.c \
		vector_product.c \
		color.c \
		color2.c \
		ray.c \
		quaternion.c \
		quaternion2.c \
		camera.c\
		equations.c \
		shape.c \
		primitives/sphere.c \
		primitives/sphere_color.c \
		primitives/cylinder.c \
		primitives/cylinder_color.c \
		primitives/cylinder_intersection.c \
		primitives/cone.c \
		primitives/cone_color.c \
		primitives/cone_intersection.c \
		primitives/plane_color.c \
		primitives/plane.c

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

$(LIB): $(OBJS)
	ar rcs $(addprefix $(LIB_PATH), $(NAME)) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(addprefix $(LIB_PATH), $(NAME))

re: fclean $(addprefix $(LIB_PATH), $(NAME))
