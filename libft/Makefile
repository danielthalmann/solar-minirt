# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 09:07:29 by trossel           #+#    #+#              #
#    Updated: 2022/05/25 12:06:53 by trossel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= gcc
CFLAGS 		= -Wall -Wextra -Werror #-g -fsanitize=address -fno-omit-frame-pointer
TARGET 		= libft.a
SRCS_DIR 	= src
OBJS_DIR 	= $(SRCS_DIR)
INCLUDES	= -Iinclude
_SRCS = ft_isalpha.c \
	   ft_isdigit.c \
	   ft_isalnum.c \
	   ft_isascii.c \
	   ft_isprint.c \
	   ft_strlen.c \
	   ft_memset.c \
	   ft_bzero.c \
	   ft_memcpy.c \
	   ft_memmove.c \
	   ft_strlcat.c \
	   ft_strlcpy.c \
	   ft_tolower.c \
	   ft_toupper.c \
	   ft_atoi.c \
	   ft_atol.c \
	   ft_atof.c \
	   ft_strnstr.c \
	   ft_strncmp.c \
	   ft_strchr.c \
	   ft_strrchr.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_calloc.c \
	   ft_strdup.c \
	   ft_strjoin.c \
	   ft_strcut.c \
	   ft_strtrim.c \
	   ft_substr.c \
	   ft_itoa.c \
	   ft_utoa.c \
	   ft_hextoa.c \
	   ft_split.c \
	   ft_strmapi.c \
	   ft_striteri.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   get_next_line.c \
	   ft_is_white_space.c \
	   ft_printf/ft_printf.c \
	   ft_printf/ft_printf_conversion.c \
	   ft_printf/print_char.c \
	   ft_printf/print_string.c \
	   ft_printf/print_int.c \
	   ft_printf/print_unsigned.c \
	   ft_printf/print_hex.c \
	   ft_printf/print_p.c \
	   ft_scanf/ft_scanf.c \
	   ft_scanf/ft_scanf_conversion.c \
	   ft_scanf/scan_char.c \
	   ft_scanf/scan_int.c \
	   ft_scanf/scan_float.c

_SRCS_BONUS = ft_lstnew.c \
	   ft_lstadd_front.c \
	   ft_lstsize.c \
	   ft_lstlast.c \
	   ft_lstadd_back.c \
	   ft_lstdelone.c \
	   ft_lstclear.c \
	   ft_lstiter.c \
	   ft_lstmap.c
OBJS_BONUS = $(patsubst %.c, $(OBJS_DIR)/%.o, $(_SRCS_BONUS))

OBJS = $(patsubst %.c, $(OBJS_DIR)/%.o, $(_SRCS))
SRCS = $(patsubst %, $(SRCS_DIR)/%, &(_SRCS))

TESTS_DIR = ./test
_TESTS_SRCS = test_ft_sscanf.c \
			  test_ft_atof.c
TESTS_SRCS = $(patsubst %.c, $(TESTS_DIR)/%.o, $(_TESTS_SRCS))
TESTS_EXECS = $(patsubst %.c, $(TESTS_DIR)/%.out, $(_TESTS_SRCS))

.PHONY : all clean fclean re bonus test clean_test


$(TARGET): $(OBJS)
	ar rcs $(TARGET) $(OBJS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(TARGET)
	rm -f $(TESTS_EXECS)

re: fclean all

$(OBJS_DIR):
	@mkdir -p $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) -c $(CFLAGS) -o $@ $^ $(INCLUDES)

$(TESTS_DIR)/%.out : $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDES) $(TARGET)

clean_test:
	rm -rf $(TESTS_EXECS)

test: clean_test $(TARGET) $(TESTS_EXECS)

bonus: $(OBJS_BONUS) | $(TARGET)
	ar rcs $(TARGET) $(OBJS_BONUS)

%.out: $(TARGET) bonus $(SRCS_DIR)/%.c
	gcc -g $(CFLAGS) $< $(TARGET) -o $@ $(INCLUDES)

tests:

norminette:
	@norminette $(SRCS_DIR) includes
