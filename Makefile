NAME	= pipex
# CFLAGS	= -Wall -Werror -Wextra
CFLAGS	= -g

LFTDIR	= ./libft
LIBFT	= $(LFTDIR)/libft.a

LIBS	= $(LIBFT)
SRCDIR	= ./src
SRC		=	$(SRCDIR)/execute.c \
			$(SRCDIR)/pipex.c \
			$(SRCDIR)/utils.c

OBJS	= ${SRC:.c=.o}

all: $(NAME)

$(LIBFT):
	make -C $(LFTDIR) all

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

clean:
	make -C $(LFTDIR) clean
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re
