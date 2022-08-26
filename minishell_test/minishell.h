#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef union u_arg
{
	int			nb;
	long long	ln;
	char		ch;
	char		*str;
	void		*ptr;
} t_arg;

enum e_type
{
	INT,
	LONG_LONG,
	CHAR,
	STRING,
	PTR
};

typedef struct s_lst
{
	char			*str;
	int				tok;
	struct s_lst	*next;
} t_lst;

typedef struct s_cmd
{
	char		*name;
	int			l_pipe[2];
	int 		r_pipe[2];
	char		*imt_file;
	char		*otp_file;
	enum e_type	arg_type;
	t_arg		arg;
	char		opt;
	void		*f;
} t_cmd;

enum e_blt_in
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
//	EXIT,
	NO
};

typedef struct s_func
{
	enum e_blt_in	b_cmd;
	void			*f;
} t_func;

typedef struct s_data
{
	t_cmd			*cmd;
	struct s_data	*next;
} t_data;

typedef struct s_exec
{
	char			*line;
//	int				exit;
	t_lst			*lst;
	t_data			*data;
} t_exec;

#define CLOSE "\001\033[0m\002"                 // Закрыть все свойства
#define BLOD  "\001\033[1m\002"                 // Подчеркнуть, жирным шрифтом, выделить
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"    // x: background, y: foreground

void	exit_on_err(char *msg);
void	free_lst(t_lst *lst);
void	free_all(void);
void	init_struct(void);
t_lst	*init_list(void);
t_lst	*add_lst_node(t_lst *prev);
t_lst	*make_lst(char **wrd_list);
t_lst	*lexer_expander(char *line);
t_lst	*fill_struct(char *line);


#endif