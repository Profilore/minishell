/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:49:29 by aperez-b          #+#    #+#             */
/*   Updated: 2022/03/07 21:16:45 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_status;

void	child_builtin(t_prompt *prompt, t_mini *n, int l, t_list *cmd)
{
//debug
//	printf("child_builtin starts\n");

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!is_builtin(n) && n->full_cmd)
	{
//debug		
//		printf("child_builtin execve\n");
//		printf("child_builtin n->full_path=%s\n", n->full_path);
//		printf("child_builtin n->full_cmd[0]=%s\n", n->full_cmd[0]);
//		printf("child_builtin prompt->envp[0]=%s\n", prompt->envp[0]);
		execve(n->full_path, n->full_cmd, prompt->envp);
	}
	else if (n->full_cmd && !ft_strncmp(*n->full_cmd, "pwd", l) \
		&& l == 3)
		g_status = mini_pwd();
	else if (is_builtin(n) && n->full_cmd && \
		!ft_strncmp(*n->full_cmd, "echo", l) && l == 4)
		g_status = mini_echo(cmd);
	else if (is_builtin(n) && n->full_cmd && \
		!ft_strncmp(*n->full_cmd, "env", l) && l == 3)
	{
		ft_putmatrix_fd(prompt->envp, 1, 1);
		g_status = 0;
	}
	else if (is_builtin(n) && n->full_cmd && \
		!ft_strncmp(*n->full_cmd, "export", l) && l == 6)
	{
		ft_putmatrix_fd(prompt->declare, 1, 1);
		g_status = 0;
	}
}

static void	*child_redir(t_list *cmd, int fd[2])
{
//debug	
//	printf("child_redir starts\n");
	t_mini	*node;

	node = cmd->content;
//	printf("infile=%d\t outfile=%d\n", node->infile, node->outfile);
	if (node->infile != STDIN_FILENO)
	{
//		printf("child_redir node->infile=%d != STDIN_FILENO\n", node->infile);
		if (dup2(node->infile, STDIN_FILENO) == -1)
		{
//			printf("ch_redir if(dup2(infile)) return mini_perror(DUPERR, NULL, 1)\n");
			return (mini_perror(DUPERR, NULL, 1));
		}
		close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO)
	{
//		printf("child_redir node->outfile != STDIN_FILENO\n");
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
		{
//			printf("ch_redir if(dup2(outfile)) return mini_perror(DUPERR, NULL, 1)\n");
			return (mini_perror(DUPERR, NULL, 1));
		}
		close(node->outfile);
	}
	else if (cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
	{
//		printf("ch_redir if(cmd->next && dup2(fd[WRITE_END])) return mini_perror(DUPERR, NULL, 1)\n");
		return (mini_perror(DUPERR, NULL, 1));
	}
//	printf("child_redir before close(fd[WRITE_END]) \n");
	close(fd[WRITE_END]);
//	printf("child_redir\"\" return empty str\n" );
	return ("");
}

void	*child_process(t_prompt *prompt, t_list *cmd, int fd[2])
{
//debug
//	printf("child_process starts getpid=%d\n", getpid());	
	t_mini	*n;
	int		l;

	n = cmd->content;
	l = 0;
	if (n->full_cmd)
		l = ft_strlen(*n->full_cmd);
//debgu
//	printf("child_process->child_redir getpid=%d\n", getpid());	
	child_redir(cmd, fd);
	close(fd[READ_END]);
//	printf("child_process->child_builtin\n");	
	child_builtin(prompt, n, l, cmd);
	ft_lstclear(&prompt->cmds, free_content);
	exit(g_status);
}

void	exec_fork(t_prompt *prompt, t_list *cmd, int fd[2])
{
//debug
//	printf("exec_fork starts getpid=%d\n", getpid());	
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
//		printf("exec_fork if (pid < 0) getpid=%d\n", getpid());
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		mini_perror(FORKERR, NULL, 1);
	}
	else if (!pid)
	{
//		printf("exec_fork else if (!pid) getpid=%d\n", getpid());
		child_process(prompt, cmd, fd);
	}
}

void	*check_to_fork(t_prompt *prompt, t_list *cmd, int fd[2])
{
//debug
//	printf("check_to_fork starts getpid=%d\n", getpid());	
	t_mini	*n;
	DIR		*dir;

	n = cmd->content;
	dir = NULL;
	if (n->full_cmd)
	{
//		printf("check_to_fork n->full_cmd[0]=%s\n", n->full_cmd[0]);
//		printf("check_to_fork n->full_cmd[1]=%s\n", n->full_cmd[1]);
		dir = opendir(*n->full_cmd);
	}
	if (n->infile == -1 || n->outfile == -1)
	{
//		printf("check_to_fork if(infile==-1 || outfile==-1) return NULL\n");
		return (NULL);
	}
//debug	
	int is_built;
	int acces;
	is_built = is_builtin(n);
	acces = access(n->full_path, X_OK);
//	printf("check_to_fork is_built = %d\n", is_built);
//	printf("check_to_fork  acces= %d\n", acces);
//	printf("check_to_fork n->full_path=%s\n", n->full_path);

//	if ((n->full_path && access(n->full_path, X_OK) == 0) || is_built)
	if ((n->full_path && acces == 0) || is_built)
	{
//		printf("check_to_fork -> exec_fork\n");
		exec_fork(prompt, cmd, fd);
	}
	else if (!is_builtin(n) && ((n->full_path && \
		!access(n->full_path, F_OK)) || dir))
//debug chandge 126 to 0		
		g_status = 126;
	else if (!is_builtin(n) && n->full_cmd)
		g_status = 127;
	if (dir)
		closedir(dir);
//	printf("check_to_fork return \"\" empty str getpid=%d\n", getpid());
	return ("");
}
