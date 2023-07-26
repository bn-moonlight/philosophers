NAME =		philo_bonus
CC =		gcc
FLAGS =		-Wall -Werror -Wextra -pthread
RM =		rm -rf

SRC =		philo_bonus.c \
			dinner_bonus.c \
			utils_bonus.c

OBJECTS =	$(SRC:.c=.o)

.c.o:
			@ $(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME) text

$(NAME):	$(OBJECTS) philo_bonus.h
			@ $(CC) $(FLAGS) $(OBJECTS) -o $(NAME)
			@echo "\x1B[35m"Compile Done!"\x1b[0m"

clean:
			@ $(RM) $(OBJECTS)
			@echo "\x1b[36m"Object files deleted."\x1b[0m"

fclean:		clean
			@ $(RM) $(NAME)
			@echo "\x1b[36m"Program deleted."\x1b[0m"

re:			fclean all

text:
	@echo "\x1b[36m"by sakkaya"\x1b[0m"

.PHONY:		all clean fclean re
