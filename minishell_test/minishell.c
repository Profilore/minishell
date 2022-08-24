#include "minishell.h"
#include "libft/libft.h"

t_exec	*exec;

void	exit_on_err(char *msg)
{
	ft_putstr_fd(msg, 2);
	free_all();
	exit(1);
}

void	free_lst(void)
{
	t_lst	*tmp;

	while (exec->lst->next != NULL)
	{
		tmp = exec->lst->next;
		free(exec->lst->str);
		free(exec->lst);
		exec->lst = tmp;
	}
	free(exec->lst->str);
	free(exec->lst);
	exec->lst = NULL;
}

void	free_all(void)
{
	t_data	*tmp;

	while (exec->data->next != NULL)
	{
		tmp = exec->data->next;
		free(exec->data->cmd);
		free(exec->data);
		exec->data = tmp;
	}
	free_lst();
	free(exec->data->cmd);
	free(exec->data);
	free(exec->line);
	free(exec);
}

t_cmd	*init_str_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		exit_on_err("failed malloc");
	cmd->name = NULL;
	cmd->l_pipe[0] = 0;
	cmd->l_pipe[1] = 0;
	cmd->r_pipe[0] = 0;
	cmd->r_pipe[1] = 0;
	cmd->imt_file = NULL;
	cmd->otp_file = NULL;
	cmd->arg_type = INT;
	cmd->arg.nb = 0;
	cmd->opt = 0;
	cmd->f = NULL;
	return (cmd);
}

t_data	*init_str_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit_on_err("failed malloc");
	data->cmd = init_str_cmd();
	data->next = NULL;
	return (data);
}

void	init_struct(void)
{
	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		exit_on_err("failed malloc");
	exec->exit = 0;
	exec->line = NULL;
	exec->lst = NULL;
	exec->data = init_str_data();
}

t_lst	*init_list(void)
{
	t_lst	*lst;

	lst = (t_lst *)malloc(sizeof(t_lst));
	if (!lst)
		exit_on_err("failed listing");
	lst->str = NULL;
	lst->tok = 0;
	lst->next = NULL;
	return (lst);
}

t_lst	*add_lst_node(t_lst *prev)
{
	t_lst	*new;

	new = init_list();
	prev->next = new;
	return (new);
}

void	make_lst(char **wrd_list)
{
	char	*content;
	int		len;
	int		i;
	t_lst	*tmp;

	i = 0;
	exec->lst = init_list();
	tmp = exec->lst;
	while (wrd_list[i])
	{
		printf("word %i: %s\n", i, wrd_list[i]);
		i++;
	}
	i = 0;
	while (wrd_list[i])
	{
		len = ft_strlen(wrd_list[i]) + 1;
		content = malloc(len);
		if (!content)
		{
			free_lst();
			exit_on_err("failed malloc");
		}
		ft_strlcpy(content, wrd_list[i], len);
		printf("content: %s\n", content);
		tmp->str = content;
		printf("%s\n", tmp->str);
		i++;
		tmp->next = add_lst_node(tmp);// one list node too many lol
		tmp = tmp->next;
	}
	i = 0;
	while (wrd_list[i])
	{
		free(wrd_list[i]);
		i++;
	}
	free(wrd_list);
}

void	lexer_expander(char *line)
{
	char	**wrd_list;

	wrd_list = ft_split(line, ' ');
	if (!wrd_list)
		exit_on_err("failed split");
	make_lst(wrd_list);
//	check_quotes();
//	check_redrir_pipes();
//	check_env_vars();
}

void	fill_struct(char *line)
{
	t_lst	*tmp;

	tmp = exec->lst;
	lexer_expander(line);
	if (!ft_strncmp(exec->lst->str, "exit", 4))
	{
		free_all();
		exit(0);
	}
	while (exec->lst->next != NULL)
	{
		printf("%s, ", exec->lst->str);
		exec->lst = exec->lst->next;
	}
	printf("%s \n", exec->lst->str);
}
/*
void		do_stuff(t_exec *exec)
{
	if (exec->exit != 0)
	{
		free_all(exec);
		return ;
	}
}*/

int	main()
{
	char	*line;

	init_struct();
	line = readline(BEGIN(49, 34)"Myshell $> "CLOSE);
	if (!line)
		exit(0);
	while (1)
	{
		add_history(line);
		fill_struct(line);
//		do_stuff(exec);
//		if (exec->exit != 0)
//			break ;
		free(line);
		line = readline(BEGIN(49, 34)"Myshell $> "CLOSE);
	}
	free(line);
	return (0);
}
