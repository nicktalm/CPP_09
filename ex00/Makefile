NAME = btc
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++17
SOURCE = main.cpp BitcoinExchange.cpp
OBJ_DIR = objs
OBJS = $(addprefix $(OBJ_DIR)/, $(SOURCE:.cpp=.o))

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all: $(NAME)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re