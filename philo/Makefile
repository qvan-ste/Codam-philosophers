RED =\033[0;31m
ORANGE=\033[0;33m
GREEN =\033[0;32m
NO_COLOUR =\033[0m

CFILES = init.c main.c simulation.c time.c status.c utils.c

OFILES = $(CFILES:.c=.o)

CFLAGS = -Wall -Werror -Wextra -fsanitize=thread

NAME = philo

all: $(NAME)

.c.o:
	@echo "$(ORANGE)[$(NAME)] Compiling $<$(NO_COLOUR)"
	@$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(OFILES) 
	@$(CC) $(CFLAGS) $(OFILES) -o $(NAME)
	@echo "$(GREEN)[$(NAME)] Compiling finished$(NO_COLOUR)"


clean:
	@rm -f $(OFILES)
	@echo "$(RED)[$(NAME)] Removing .o files$(NO_COLOUR)"

fclean:  clean
	@rm -f $(NAME)
	@echo "$(RED)[$(NAME)] Removing $(NAME)$(NO_COLOUR)"

re: fclean all

.PHONY:  all clean fclean re .c.o