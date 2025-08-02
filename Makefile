NAME = philo

INC 	= philo.h

SRC		=	philo.c\
			init.c\
			utils.c\
			process.c\
			actions.c\
			free_destroy.c
	

FLAGS	= -Wall -Wextra -Werror -pthread #-fsanitize=address #-g -fsanitize=thread 

OBJS 	= $(SRC:.c=.o)

$(NAME): $(OBJS)
	gcc $(FLAGS) $(SRC) -o $(NAME) #compile

all: $(NAME) $(OBJS) $(INC)

%.o: %.c $(INC) 
		gcc $(FLAGS) -c $< -o $@ #make object files

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
