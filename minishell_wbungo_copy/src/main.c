/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavinia <nlavinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:40:47 by nlavinia          #+#    #+#             */
/*   Updated: 2022/10/11 02:02:59 by nlavinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_status;

static t_prompt	init_vars(t_prompt prompt, char *str, char **argv)
{
	char	*num;

	str = getcwd(NULL, 0);
	prompt.envp = mini_setenv("PWD", str, prompt.envp, 3);
	free(str);
	str = mini_getenv("SHLVL", prompt.envp, 5);
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
	free(str);
	prompt.envp = mini_setenv("SHLVL", num, prompt.envp, 5);
	free(num);
	str = mini_getenv("PATH", prompt.envp, 4);
	if (!str)
		prompt.envp = mini_setenv("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.envp, 4);
	free(str);
	str = mini_getenv("_", prompt.envp, 1);
	if (!str)
		prompt.envp = mini_setenv("_", argv[0], prompt.envp, 1);
	free(str);
	return (prompt);
}

static t_prompt	init_prompt(char **argv, char **envp)
{
	t_prompt	prompt;
	char		*str;

	str = NULL;
	prompt.cmds = NULL;
	prompt.envp = ft_dup_matrix(envp);
	g_status = 0;
	prompt.pid = getpid();
	prompt = init_vars(prompt, str, argv);
	return (prompt);
}

char	*add_newline(char *str)
{
	char	*newstr;

	newstr = malloc(ft_strlen(str) + 2);
	ft_strlcpy(newstr, str, (ft_strlen(str) + 1));
	ft_strlcat(newstr, "\n", (ft_strlen(newstr) + 2));
	return (newstr);
}

int	main(int argc, char **argv, char **envp)
{
	char				*str;
	char				*out;
	t_prompt			prompt;

	rl_catch_signals = 0;
	prompt = init_prompt(argv, envp);
	while (argv && argc)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		str = mini_getprompt(prompt);
		if (str)
			out = readline(str);
		else
			out = readline("guest@minishell $ ");
		free(str);
		if (!check_args(out, &prompt))
			break ;
	}
	exit(g_status);
}
