S = src
B = bonus
I = inc
O = obj
OO = ft_printf/src

SRC = $(wildcard $(S)/*.c)
OSRC = $(wildcard $(OO)/*.c)
SRC_BONUS = $(wildcard $(B)/*.c)
OBJ = $(patsubst $(S)/*.c,$(O)/%.o,$(SRC))
OOBJ = $(patsubst $(OO)/*.c,$(OO)/%.o,$(OSRC))

CC  = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -pthread -I $(I)
RM = rm -f
RMDIR = rm -rf
NAME = philo
NAME_B = philo_bonus
PRINTF = ft_printf/libftprintf.a
# LIBFT = libft/libft.a
# GNL = get_next_line/gnl.a

all : $(NAME)

bonus : $(NAME_B)

$(O):
		@mkdir -p $@

$(OBJ): | $(O)
$(OOBJ): | $(OO)

$(O)/%.o : $(S)/%.c
		$(CC) $(CFLAGS) -c $< -o $@

$(OO)/%.o : $(OO)/%.c
		$(CC) $(CFLAGS) -c $< -o $@

$(O)/%.o : $(B)/%.c
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(OOBJ)
		$(MAKE) -C ft_printf
		$(CC) $(CFLAGS) $(OBJ) $(PRINTF) -o $@

$(NAME_B): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $@

cleanobj:
		$(RM) $(wildcard $(O)/*.o)
		$(RM) $(wildcard $(OO)/*.o)

cleanobjdir: cleanobj
		$(RMDIR) $(O)

clean: cleanobjdir

fclean: clean
		$(RM) $(NAME) $(PRINTF)

re: fclean all

.PHONY: all clean fclean re
