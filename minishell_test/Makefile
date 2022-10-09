NAME	=	minishell
SRC		=	minishell.c
HEADER	=	minishell.h
OBJ		=	${SRC:.c=.o}
CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror -g 
LIBFT	=	libft/libft.a
UNAME	:=	'uname'

RDL_H	=	-I /usr/local/opt/readline/include
RDL_L	=	-L /usr/local/opt/readline/lib

RDL_H1	=	-I /usr/local/Cellar/readline/8.1.2/include
RDL_L1	=	-L /usr/local/Cellar/readline/8.1.2/lib
CHECK	=	just check

.PHONY: all clean fclean re

# ifeq ($(UNAME),Linux)
# #Properties for Linux
# 			${NAME}:	${OBJ} ${HEADER}
# 						@${CC} -lreadline ${OBJ} -o ${NAME}
# 						@echo "minishell compiled successfully!"	

# endif

${NAME}:	${OBJ} ${HEADER} ${LIBFT}
			@${CC} ${RDL_H} ${RDL_L} ${RDL_H1} ${RDL_L1} \
			-lreadline ${OBJ} ${LIBFT} -o ${NAME}
#			@${CC} ${OBJ} ${LIBFT} -o ${NAME}
			@echo "minishell compiled successfully!"

${LIBFT}:	
			make -C ./libft all

%.o:%.c		${HEADER}
			${CC} ${RDL_H} ${RDL_H1} \
			${CFLAGS} -I ./libft -c $< -o ${<:.c=.o}

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
