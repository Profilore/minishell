/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavinia <nlavinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 12:08:12 by nlavinia          #+#    #+#             */
/*   Updated: 2022/10/11 02:09:16 by nlavinia         ###   ########.fr       */
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

int	return_exit_status(int ex_return)
{
	ex_return %= 256;
	if (ex_return < 0)
		ex_return = 256 + ex_return;
	return (ex_return);
}

static void	*parse_args(char **args, t_prompt *p)
{
	int	is_exit;

	is_exit = 0;
	p->cmds = fill_nodes(split_all(args, p), -1);
	if (!p->cmds)
		return (p);
	g_status = builtin(p, p->cmds, &is_exit, 0);
	if (!is_exit && g_status == 13)
		g_status = 0;
	if (!is_exit && g_status == 126)
	{
		g_status = 126;
		return (0);
	}
	if (!is_exit && WIFSIGNALED(g_status) && WTERMSIG(g_status))
	{
		g_status = 128 + WTERMSIG(g_status);
		return (p);
	}
	if (is_exit && WIFSIGNALED(g_status))
		g_status = return_exit_status(g_status);
	if (args && is_exit)
	{
		ft_lstclear(&p->cmds, free_content);
		return (NULL);
	}
	g_status = WSTOPSIG(g_status);
	return (p);
}

void	*check_args(char *out, t_prompt *p)
{
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
