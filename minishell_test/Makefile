NAME	=	minishell
SRC		=	minishell.c
HEADER	=	minishell.h
OBJ		=	${SRC:.c=.o}
CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror -g 
LIBFT	=	libft/libft.a
UNAME	:=	'uname'
.PHONY: all clean fclean re

# ifeq ($(UNAME),Linux)
# #Properties for Linux
# 			${NAME}:	${OBJ} ${HEADER}
# 						@${CC} -lreadline ${OBJ} -o ${NAME}
# 						@echo "minishell compiled successfully!"	

# endif

${NAME}:	${OBJ} ${HEADER} ${LIBFT}
			@${CC} -lreadline ${OBJ} ${LIBFT} -o ${NAME}
			@echo "minishell compiled successfully!"

${LIBFT}:	
			make -C ./libft all

%.o:%.c		${HEADER}
			${CC} ${CFLAGS} -I ./libft -c $< -o ${<:.c=.o}

all:		${NAME}

clean:		
			@make -C ./libft clean
			@rm -f ${OBJ}
			@echo "fclean successfull!"

fclean:		
			@make -C ./libft fclean
			@rm -f ${OBJ} ${NAME}
			@echo "fclean successfull!"

re:			fclean all
