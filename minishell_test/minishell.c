#include "minishell.h"
#include "libft/libft.h"

/*t_exec	*exec;

void	exit_on_err(char *msg)
{
	ft_putstr_fd(msg, 2);
	free_all();
	exit(1);
}*/

void	free_lst(t_lst *lst)
{
	t_lst	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->str);
		free(tmp);
	}
}
/*
void	free_all(void)
{
	t_data	*tmp;

	while (exec->data != NULL)
	{
		tmp = exec->data;
		exec->data = exec->data->next;
		free(tmp->cmd);
		free(tmp);
	}
	free_lst(exec->lst);
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
//	exec->exit = 0;
	exec->line = NULL;
	exec->lst = NULL;
	exec->data = init_str_data();
}
*/
t_lst	*init_list(void)
{
	t_lst	*lst;

	lst = (t_lst *)malloc(sizeof(t_lst));
/*	if (!lst)
		exit_on_err("failed listing");*/
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

t_lst	*make_lst(char **wrd_list)
{
	char	*content;
	t_lst	*lst;
	int		len;
	int		i;
	t_lst	*tmp;

	i = 0;
	lst = init_list();
	tmp = lst;
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
			free_lst(lst);
//			exit_on_err("failed malloc");
		}
		ft_strlcpy(content, wrd_list[i], len);
		printf("content: %s\n", content);
		tmp->str = content;
		printf("%s\n", tmp->str);
		i++;
		if (wrd_list[i])
		{
			tmp->next = add_lst_node(tmp);// one list node too many lol
			tmp = tmp->next;
		}
	}
	i = 0;
	while (wrd_list[i])
	{
		free(wrd_list[i]);
		i++;
	}
	free(wrd_list);
	return (lst);
}

t_lst	*lexer_expander(char *line)
{
	char	**wrd_list;
	t_lst	*lst;

	wrd_list = ft_split(line, ' ');
/*	if (!wrd_list)
		exit_on_err("failed split");*/
	lst = make_lst(wrd_list);
//	check_quotes();
//	check_redrir_pipes();
//	check_env_vars();
	return (lst);
}

t_lst	*fill_struct(char *line)
{
	t_lst	*lst;
	t_lst  	*tmp;

	lst = lexer_expander(line);
	tmp = lst;
	if (lst && lst->str)
		if (!ft_strncmp(lst->str, "exit", 4))
		{
			// free_all();
			exit(0);
		}
	while (lst != NULL)
	{
		printf("%s, ", lst->str);
		lst = lst->next;
	}
	return (tmp);
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
	t_lst	*lst;

//	init_struct();
	line = readline(BEGIN(49, 34)"Myshell $> "CLOSE);
	if (!line)
		exit(0);
	while (1)
	{
		add_history(line);
		lst = fill_struct(line);
//		do_stuff(exec);
//		if (exec->exit != 0)
//			break ;
		free_lst(lst);
		free(line);
		line = readline(BEGIN(49, 34)"Myshell $> "CLOSE);
	}
	free(line);
	return (0);
}
