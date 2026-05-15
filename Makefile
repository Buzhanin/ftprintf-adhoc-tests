SOURCES = test.c

FT_PRINTF_FOLDER = ../ft_printf
FT_PRINTF_NAME = libftprintf.a

OBJECTS = $(SOURCES:.c=.o)
OBJECTS_ORIGINAL = $(SOURCES:.c=_original.o)

NAME = test_libftprintf
NAME_ORIGINAL = test_libftprintf_original

CFLAGS = -g -Wall -Wextra -Werror -I$(FT_PRINTF_FOLDER) -I$(FT_PRINTF_FOLDER)/libft $(shell pkg-config --cflags glib-2.0)
LDFLAGS = -L$(FT_PRINTF_FOLDER) -lftprintf $(shell pkg-config --libs glib-2.0)

all: $(NAME)
	./$(NAME)

original: $(NAME_ORIGINAL)
	./$(NAME_ORIGINAL)

$(OBJECTS): %.o: %.c
	cc $(CFLAGS) -c $^ -o $@

$(OBJECTS_ORIGINAL): %_original.o: %.c
	cc $(CFLAGS) -DORIGINAL -c $^ -o $@

$(NAME): $(FT_PRINTF_FOLDER)/$(FT_PRINTF_NAME) $(OBJECTS)
	cc -o $(NAME) $(OBJECTS) $(LDFLAGS)

$(NAME_ORIGINAL): $(FT_PRINTF_FOLDER)/$(FT_PRINTF_NAME) $(OBJECTS_ORIGINAL)
	cc -o $(NAME_ORIGINAL) $(OBJECTS_ORIGINAL) $(LDFLAGS)

$(FT_PRINTF_FOLDER)/$(FT_PRINTF_NAME): FORCE
	make -C $(FT_PRINTF_FOLDER)

FORCE:

fclean: clean
	rm -f $(NAME) $(NAME_ORIGINAL)
	make -C $(FT_PRINTF_FOLDER) fclean

clean:
	rm -f $(OBJECTS) $(OBJECTS_ORIGINAL)
	make -C $(FT_PRINTF_FOLDER) clean

re: fclean all
