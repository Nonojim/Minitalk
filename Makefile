#sources files
SRC = server.c client.c
#append .o to each .c files in the SRC
#OBJS := $(SRC:%.c=%.o)
OBJS = ${SRC:.c=.o}
#build target name
NAME = minitalk
#compiler
CC = gcc
#compiler flags
CCFLAGS = -Wall -Wextra -Werror
#include directory == dossier includes
INC_DIR = .
#preprocessor flag
CPPFLAGS = -I $(INC_DIR) -I printf -I printf/libft
#rm
RM = rm -f
#archive
ARNAME = ar rcs $(NAME)
#index generator for the archive so the linkers could find ft and variables
RANNAME = ranlib $(NAME)

#first rull is always "all" she is calling $(NAME)
all: $(NAME)
#NAME
$(NAME): server client

server:	server.o
		@make -C printf
	$(CC) $(CCFLAGS) server.o printf/libftprintf.a printf/libft/libft.a -o server

client:	client.o
		@make -C printf
	$(CC) $(CCFLAGS) client.o printf/libftprintf.a printf/libft/libft.a -o client
# "%.o" rule compie .c file into corresponding .o file
# "%" is a wildcard for "name of the files without extension"
# $@ = target, here target = .o "$<" = first dependencies here = .c
%.o: %.c
	$(CC) $(CPPFLAGS) $(CCFLAGS) -o $@ -c $<
#clean delete all .o files
clean:
	$(RM) $(OBJS)
	@make -C printf clean
#after executing clean delete the lib
fclean: clean
	$(RM) server client
	@make -C printf fclean
#delete everything then re create it
re: fclean all
#phony targets
.PHONY: all clean fclean re
