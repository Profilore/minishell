/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 12:08:12 by aperez-b          #+#    #+#             */
/*   Updated: 2022/03/07 21:26:20 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_status;

static char	**split_all(char **args, t_prompt *prompt)
{
	char	**subsplit;
	int		i;
	int		quotes[2];

	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], -1, quotes, prompt);
		args[i] = expand_path(args[i], -1, quotes, \
			mini_getenv("HOME", prompt->envp, 4));
		subsplit = ft_cmdsubsplit(args[i], "<|>");
		ft_matrix_replace_in(&args, subsplit, i);
		i += ft_matrixlen(subsplit) - 1;
		ft_free_matrix(&subsplit);
	}
	return (args);
}
/*
static void	*parse_args(char **args, t_prompt *p)
{
	int	is_exit;
	int	i;

	is_exit = 0;
	p->cmds = fill_nodes(split_all(args, p), -1);
	if (!p->cmds)
		return (p);
	i = ft_lstsize(p->cmds);
	g_status = builtin(p, p->cmds, &is_exit, 0);
	while (i-- > 0)
		waitpid(-1, &g_status, 0);
	if (!is_exit && g_status == 13)
		g_status = 0;
	if (g_status > 255)
		g_status = g_status / 255;
	if (args && is_exit)
	{
		ft_lstclear(&p->cmds, free_content);
		return (NULL);
	}
	return (p);
}
*/

int	return_exit_status(int ex_return)
{
//	printf("ex_return_0=\t%lld\n", ex_return);
	ex_return %= 256;
//	printf("ex_return_1=\t%lld\n", ex_return);
	if (ex_return < 0)
		ex_return = 256 + ex_return;
//	printf("ex_return_2=\t%lld\n", ex_return);
	return (ex_return);
}


static void	*parse_args(char **args, t_prompt *p)
{
	int	is_exit;
	int	i;
//debug
/*	
	int compare_str;
	printf("parse_args g_status 0=%d\n", g_status);	
	if (args[0])
	{
		printf("args[0]=%s\n", args[0]);
		compare_str = ft_strncmp(args[0], "cat\n", 4);
		printf("compare_str=%d\n", compare_str);
	}
	else
		printf("args[0] = NULL\n");
*/
/*
	if (args[1])
	{
		printf("args[1]=%s\n", args[1]);
		compare_str = ft_strncmp(args[1], "cat\n", 4);
		printf("compare_str=%d\n", compare_str);
	}
	else
		printf("args[1] = NULL\n");
*/
	is_exit = 0;
	p->cmds = fill_nodes(split_all(args, p), -1);
	if (!p->cmds)
//debug
//	{
//		printf("!p->cmds\n");
		return (p);
//	}
	i = ft_lstsize(p->cmds);
//	printf("parse_args->builtin\n");
	g_status = builtin(p, p->cmds, &is_exit, 0);
//debug
//	printf("parse_args g_status 1=%d\n", g_status);	
//	printf("is_exit_0=%d\n", is_exit);
	while (i-- > 0)
	{
//		printf("waitpid starts getpid=%d\n", getpid());
		waitpid(-1, &g_status, 0);
//		printf("waitpid returns getpid=%d\n", getpid());
//		printf("waitpid g_status=%d\n", g_status);	
	}
	printf("g_status 0=%d\n", g_status);
	printf("WIFEXITED(g_status)=%d\n",WIFEXITED(g_status));
	printf("WEXITSTATUS(g_status)=%d\n",WEXITSTATUS(g_status));
	printf("WIFSIGNALED=%d\n", WIFSIGNALED(g_status));
	printf("WTERMSIG(status)=%d\n", WTERMSIG(g_status));
	printf("WIFSTOPPED(g_status)=%d\n", WIFSTOPPED(g_status));
	printf("WSTOPSIG(g_status)=%d\n",WSTOPSIG(g_status));
	printf("is_exit_1=%d\n", is_exit);
	
	if (!is_exit && g_status == 13)
		g_status = 0;
//	if (!is_exit && g_status == 126)
//	{
//		g_status = 126;
//		return (0);
//	}
//	if (!is_exit && g_status == 127)
//	{
//		g_status = 127;
//		return (0);
//	}
	if (!is_exit && WIFSIGNALED(g_status) && WTERMSIG(g_status))
	{
//			printf("!is exit WIFSIGNALED =%d\n", is_exit);
			g_status = 128 + WTERMSIG(g_status);
//			printf("if WIFSIGNALED g_status=\t%d\n", g_status);
//			printf("parse_argse returns p\n");
			return (p);
	}
	if (!is_exit && WTERMSIG(g_status))
	{
		g_status = WTERMSIG(g_status);
		return (p);
	}
//	printf("is_exit_2=%d\n", is_exit);
//debug
//	if (args)
//		printf("parse_args args\n");
	if (is_exit && WIFSIGNALED(g_status))
		g_status = return_exit_status(g_status);
//	printf("return exit g_status = %d\n", g_status);
//	if (is_exit && g_status > 255)
//		g_status = g_status / 255;
//	printf("is_exit_3=%d\n", is_exit);
	if (args && is_exit)
	{
		ft_lstclear(&p->cmds, free_content);
//		printf("recalculated minishell g_status=%d\n", g_status);	
//		printf("return NULL\n");
		return (NULL);
	}
//	printf("WSTOPSIG(g_status)=%d\n",WSTOPSIG(g_status));
	g_status = WSTOPSIG(g_status);
//	printf("recalculated minishell g_status=%d\n", g_status);	
//	printf("return p\n");
	return (p);
}


void	*check_args(char *out, t_prompt *p)
{
//debug	
/*	printf("check_args starts\n");
	printf("out=%s\n", out);
	int compare_str;
	compare_str = ft_strncmp(out, "cat\n", 4);
	printf("compare_str=%d\n", compare_str);
*/
/*
	if (args[1])
	{
		printf("args[1]=%s\n", args[1]);
		compare_str = ft_strncmp(args[1], "cat\n", 4);
		printf("compare_str=%d\n", compare_str);
	}
	else
		printf("args[1] = NULL\n");
*/
	char	**a;
	t_mini	*n;

	if (!out)
	{
		printf("exit\n");
		return (NULL);
	}
	if (out[0] != '\0')
		add_history(out);
	a = ft_cmdtrim(out, " ");
	free(out);
	if (!a)
		mini_perror(QUOTE, NULL, 1);
	if (!a)
		return ("");
	p = parse_args(a, p);
	if (p && p->cmds)
		n = p->cmds->content;
	if (p && p->cmds && n && n->full_cmd && ft_lstsize(p->cmds) == 1)
		p->envp = mini_setenv("_", n->full_cmd[ft_matrixlen(n->full_cmd) - 1], \
			p->envp, 1);
	if (p && p->cmds)
		ft_lstclear(&p->cmds, free_content);
	return (p);
}
