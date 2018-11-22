# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/18 12:58:48 by ebatchas          #+#    #+#              #
#    Updated: 2018/11/22 21:30:24 by ebatchas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=g++

SRCDIR=.
HEADDIR=includes
LIBDIR=lib

CFLAGS=-I$(HEADDIR) -Wall -Wextra -Werror -g -w
LDFLAGS=-I$(HEADDIR) -L$(LIBDIR) -lSDL2 -lSDL2_mixer -lSDL2_ttf

SRC=$(SRCDIR)/main.cpp)\
	$(SRCDIR)/solver.cpp\
	$(SRCDIR)/unblock.cpp\
	$(SRCDIR)/block.cpp\
	$(SRCDIR)/board.cpp\
	$(SRCDIR)/input.c\
	$(SRCDIR)/ft_tools.cpp

OBJ=$(LIBDIR)/main.o\
	$(LIBDIR)/solver.o\
	$(LIBDIR)/unblock.o\
	$(LIBDIR)/block.o\
	$(LIBDIR)/board.o\
	$(LIBDIR)/input.o\
	$(LIBDIR)/ft_tools.o
NAME = unblock-me

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^
	rm -rf "$@.dSYM"

$(LIBDIR)/%.o:$(wildcard $(HEADDDIR)/*.hpp)

$(LIBDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean fclean

clean:
	rm -rf $(LIBDIR)/*.o

fclean: clean
	rm -rf $(NAME)

re: fclean all
