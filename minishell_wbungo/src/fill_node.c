/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <mbueno-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:05:01 by aperez-b          #+#    #+#             */
/*   Updated: 2022/03/07 21:20:17 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_mini	*mini_init(void)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	mini->full_cmd = NULL;
	mini->full_path = NULL;
	mini->infile = STDIN_FILENO;
	mini->outfile = STDOUT_FILENO;
	return (mini);
}

static t_mini	*get_params(t_mini *node, char **a[2], int *i)
{
//debug
//	printf("get_params starts\n");
//	printf("*a[0]=%s\n", *a[0]);	
//	printf("*a[1]=%s\n", *a[1]);
//	printf("*i=%d\n", *i);	
	if (a[0][*i])
	{
		if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>')
			node = get_outfile2(node, a[1], i);
		else if (a[0][*i][0] == '>')
			node = get_outfile1(node, a[1], i);
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && \
			a[0][*i + 1][0] == '<')
			node = get_infile2(node, a[1], i);
		else if (a[0][*i][0] == '<')
			node = get_infile1(node, a[1], i);
		else if (a[0][*i][0] != '|')
		{
//			printf("get_params a[0][*i][0] != '|' =%c\n", a[0][*i][0]);
			node->full_cmd = ft_extend_matrix(node->full_cmd, a[1][*i]);
/*
		   printf("get_params node->full_cmd[0]=%s\n", node->full_cmd[0]);
			if (node->full_cmd[1])
				printf("get_params node->full_cmd[1]=%s\n", node->full_cmd[1]);
			else
				printf("get_params node->full_cmd[1] !=\n");
*/				
		}
		else
		{
			mini_perror(PIPENDERR, NULL, 2);
			*i = -2;
		}
//debug
/*		if (node->full_cmd)
		{
			printf("node->full_cmd[0]=%s\n", node->full_cmd[0]);
			int compare_str;
			compare_str = ft_strncmp(node->full_cmd[0], "cat\n", 4);
			printf("compare_str=%d\n", compare_str);
		}
		else
			printf("!node->full_cmd\n");
		printf("get_params return node 1\n");		
*/
		return (node);
	}
	mini_perror(PIPENDERR, NULL, 2);
	*i = -2;
	return (node);
}

static char	**get_trimmed(char **args)
{
	char	**temp;
	char	*aux;
	int		j;
//debug
/*	printf("get_trimmed\n");
	printf("args[0]=%s\n", args[0]);
	int compare_str;
	if (args[0])
	{
		compare_str = ft_strncmp(args[0], "cat\n", 4);
		printf("compare_str=%d\n", compare_str);
	}
	else
		printf("args[0] = NULL\n");
	if (args[1])
	{
		printf("args[1]=%s\n", args[1]);
		compare_str = ft_strncmp(args[1], "cat\n", 4);
		printf("compare_str=%d\n", compare_str);
	}
	else
		printf("args[1] = NULL\n");
*/
	j = -1;
	temp = ft_dup_matrix(args);
	while (temp && temp[++j])
	{
		aux = ft_strtrim_all(temp[j], 0, 0);
		free(temp[j]);
		temp[j] = aux;
	}
	return (temp);
}

static t_list	*stop_fill(t_list *cmds, char **args, char **temp)
{
//debug
//	printf("stop_fill\n");	
	ft_lstclear(&cmds, free_content);
	ft_free_matrix(&temp);
	ft_free_matrix(&args);
	return (NULL);
}

t_list	*fill_nodes(char **args, int i)
{
//debug	
/*	printf("fill_nodes starts\n");
	printf("args[0]=%s\n", args[0]);
	int compare_str;
	if (args[0])
	{
		compare_str = ft_strncmp(args[0], "cat\n", 4);
		printf("compare_str=%d\n", compare_str);
	}
	else
		printf("args[0] = NULL\n");

	if (args[1])
	{
//		printf("args[1]=%s\n", args[1]);
//		compare_str = ft_strncmp(args[1], "cat\n", 4);
//		printf("compare_str=%d\n", compare_str);
		printf("args[1] is\n");
	}
	else
		printf("args[1] = NULL\n");
*/
	t_list	*cmds[2];
	char	**temp[2];

	cmds[0] = NULL;
	temp[1] = get_trimmed(args);
	while (args[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			i += args[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(mini_init()));
			cmds[1] = ft_lstlast(cmds[0]);
		}
		temp[0] = args;
//debug
/*		if (temp[0] || temp[1])
		{
			printf("temp[0]=%s\n", *temp[0]);
			printf("temp[1]=%s\n", *temp[1]);
		}
		else
			printf("!temp[0] || !temp[1]\n");
*/
		cmds[1]->content = get_params(cmds[1]->content, temp, &i);
		if (i < 0)
			return (stop_fill(cmds[0], args, temp[1]));
		if (!args[i])
			break ;
	}
	ft_free_matrix(&temp[1]);
	ft_free_matrix(&args);
//debug
/*	if (cmds[0])
		printf("fill_nodes cmds[0]\n");
	else
		printf("fill_nodes !cmds[0]\n");
*/		
	return (cmds[0]);
}
