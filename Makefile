NAME	= pipex
# CFLAGS	= -Wall -Werror -Wextra
CFLAGS	= -g

LFTDIR	= ./libft
LIBFT	= $(LFTDIR)/libft.a

LIBS	= $(LIBFT)

SRCDIR	= ./src
SRC		=	$(SRCDIR)/execute.c \
			$(SRCDIR)/pipex2.c \
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
	rm -rf outfile.txt
	rm -rf $(OBJS)
	make -C $(LFTDIR) clean -s

fclean:
	rm -rf $(OBJS)
	rm -rf $(NAME)
	make -C $(LFTDIR) fclean

re: clean all

.PHONY: all, clean, fclean, re
