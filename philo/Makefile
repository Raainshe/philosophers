CC = cc
CC_FLAGS = -Wall -Werror -Wextra

# Targets
PHILO = philo

# Source and Object Files
SRC_FILES = ft_atoi.c \
			param_check.c \
			philosophers.c \
			cleaning.c \
			helper.c \
			initialise.c \
			monitoring.c \
			simulation.c


OBJ_FILES = $(SRC_FILES:%.c=%.o)

# Default target
all: $(PHILO)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

# Rule to create the executables
$(PHILO): $(OBJ_FILES)
	$(CC) $(CC_FLAGS) $(OBJ_FILES) -o $(PHILO)

# Clean up object files and executables
clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(PHILO)

re: fclean all

.PHONY: all clean fclean re