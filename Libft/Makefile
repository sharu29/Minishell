NAME = libft.a

S = src/
O = obj/
I = inc/

CC = cc
CFLAGS = -Wall -Wextra -Werror -c -I$I -fPIC
FLAGS = 
AR			= ar
ARFLAGS		= rcs

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c\
		ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c\
		ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c\
		ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_putchar_fd.c\
		ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_substr.c ft_strjoin.c\
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		get_next_line.c

OBJ = $(SRC:%.c=$O%.o)

RM = /bin/rm -f
RMDIR = /bin/rm -rf

.PHONY:			all clean fclean re

all: $(NAME)

$O:
	@mkdir -p $@

$(O)%.o: $(S)%.c | $O
	$(CC) $(CFLAGS) $(FLAGS) $< -o $@

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $(OBJ)

clean:
	$(RMDIR) $(O)

fclean: clean
	$(RM) $(NAME)

re: fclean all
