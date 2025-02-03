#sources files
SRC = ft_printf.c ft_count.c ft_count_unsigned.c ft_count_hex.c ft_putnbr_unsigned_fd.c ft_putnbr_hex_fd.c ft_display_c.c ft_display_s.c ft_display_i.c ft_display_psign.c ft_display_u.c ft_display_x.c ft_display_p.c
#append .o to each .c files in the SRC
#OBJS := $(SRC:%.c=%.o)
OBJS = ${SRC:.c=.o}
#build target name
NAME = libftprintf.a
#compiler
CC = gcc
#compiler flags
CCFLAGS = -Wall -Wextra -Werror
#include directory == dossier includes
INC_DIR = .
#preprocessor flag
CPPFLAGS = -I $(INC_DIR)
#rm
RM = rm -f
#archive
ARNAME = ar rcs $(NAME)
#index generator for the archive so the linkers could find ft and variables
RANNAME = ranlib $(NAME)

#first rull is always "all" she is calling $(NAME)
all: $(NAME)
#NAME
$(NAME): $(OBJS)
	@make -C libft
	cp libft/libft.a .
	mv libft.a $(NAME)
	$(ARNAME) $(OBJS)
	$(RANNAME)
# "%.o" rule compie .c file into corresponding .o file
# "%" is a wildcard for "name of the files without extension"
# $@ = target, here target = .o "$<" = first dependencies here = .c
%.o: %.c
	$(CC) $(CPPFLAGS) $(CCFLAGS) -o $@ -c $<
#clean delete all .o files
clean:
	$(RM) $(OBJS)
	$(RM) libft/*.o
#after executing clean delete the lib
fclean: clean
	$(RM) $(NAME)
	$(RM) libft/libft.a
#delete everything then re create it
re: fclean all
#phony targets
.PHONY: all clean fclean re
