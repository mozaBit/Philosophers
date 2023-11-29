SRC		= ft_printf \
		prints_one \
		prints_two	\

SRCS_DIR = ./src/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC)))

OBJS_DIR = ./src/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC)))

HEADERS	= ./include/

NAME	= libftprintf.a

CC		= gcc

AR		= ar rc

RM		= rm -f

LIB		= ranlib

FLAGS	= -Wall -Wextra -Werror

all:	${NAME}

.c.o:
		${CC} ${FLAGS} -c -I ${HEADERS} -o $@ $<

${NAME}: ${OBJS}
		${AR} $@ $^

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re
