S = src
I = inc
O = obj

SRC = $(wildcard $(S)/*.c)
OBJ = $(patsubst $(S)/*.c,$(O)/%.o,$(SRC))

CC  = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -pthread -I $(I)
RM = rm -f
RMDIR = rm -rf
NAME = philo

all : $(NAME)

bonus : $(NAME_B)

$(O):
		@mkdir -p $@

$(OBJ): | $(O)

$(O)/%.o : $(S)/%.c
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(PRINTF) -o $@

cleanobj:
		$(RM) $(wildcard $(O)/*.o)

cleanobjdir: cleanobj
		$(RMDIR) $(O)

clean: cleanobjdir

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
