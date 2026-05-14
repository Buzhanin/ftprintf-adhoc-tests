SOURCES = test.c

FT_PRINTF_FOLDER = ../ft_printf
FT_PRINTF_NAME = libftprintf.a

OBJECTS = $(SOURCES:.c=.o)

NAME = test_libftprintf

CFLAGS = -g -Wall -Wextra -Werror -I$(FT_PRINTF_FOLDER) -I$(FT_PRINTF_FOLDER)/libft $(shell pkg-config --cflags glib-2.0)
LDFLAGS = -L$(FT_PRINTF_FOLDER) -lftprintf $(shell pkg-config --libs glib-2.0)

all: $(NAME)
	./$(NAME)

$(OBJECTS): %.o: %.c
	cc $(CFLAGS) -c $^ -o $@

$(NAME): $(FT_PRINTF_FOLDER)/$(FT_PRINTF_NAME) $(OBJECTS)
	cc -o $(NAME) $(OBJECTS) $(LDFLAGS)

$(FT_PRINTF_FOLDER)/$(FT_PRINTF_NAME): FORCE
	make -C $(FT_PRINTF_FOLDER)

FORCE:

fclean: clean
	rm -f $(NAME)
	make -C $(FT_PRINTF_FOLDER) fclean

clean:
	rm -f $(OBJECTS)
	make -C $(FT_PRINTF_FOLDER) clean

re: fclean all
