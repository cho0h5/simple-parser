TARGET = parser
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++14 -fsanitize=address -g
SRCS = src/main.cpp src/lexer.cpp src/parser.cpp src/tree.cpp src/symbol_table.cpp
OBJS = $(SRCS:.cpp=.o)
SRC_DIR = ./src
INCLUDE = -Iinclude/
HEADERS = include/lexer.h include/parser.h include/tree.h include/symbol_table.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

test: all
	./$(TARGET) testcase/example1.txt

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fclean re
