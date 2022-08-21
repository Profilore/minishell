NAME	=	minishell
SRC		=	minishell.c
HEADER	=	minishell.h
OBJ		=	${SRC:.c=.o}
CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror -g 
LIBFT	=	libft.a
UNAME	:=	'uname'
.PHONY: all clean fclean re

%.o:%.c		${HEADER}
			${CC} ${CFLAGS} -I ./libft -c $< -o ${<:.c=.o}

# ifeq ($(UNAME),Linux)
# #Properties for Linux
# 			${NAME}:	${OBJ} ${HEADER}
# 						@${CC} -lreadline ${OBJ} -o ${NAME}
# 						@echo "minishell compiled successfully!"	

# endif

${NAME}:	${OBJ} ${HEADER}
			@${CC} -lreadline ${OBJ} -o ${NAME}
			@echo "minishell compiled successfully!"

${LIBFT}:	
			make -C ./libft all

all:		${LIBFT} ${NAME}

clean:		
			@make -C ./libft clean
			@rm -f ${OBJ}
			@echo "fclean successfull!"

fclean:		
			@make -C ./libft fclean
			@rm -f ${OBJ} ${NAME}
			@echo "fclean successfull!"

re:			fclean all