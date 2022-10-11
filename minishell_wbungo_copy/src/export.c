/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavinia <nlavinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:17:55 by nlavinia          #+#    #+#             */
/*   Updated: 2022/10/11 02:04:52 by nlavinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	var_in_envp(char *argv, char **envp, int ij[2])
{
	int	pos;

	ij[1] = 0;
	pos = ft_strchr_i(argv, '=');
	if (pos == -1)
		return (-1);
	while (envp[ij[1]])
	{
		if (!ft_strncmp(envp[ij[1]], argv, pos + 1))
			return (1);
		ij[1]++;
	}
	return (0);
}

int	sort(char **tmp)
{
	int		strncmp;
	int		i;
	int		j;
	char	*tmp_2;

	tmp_2 = NULL;
	i = -1;
	while ((tmp)[++i])
	{
		j = i;
		while ((tmp)[++j])
		{
			strncmp = ft_strncmp((tmp)[i], (tmp)[j], ft_strlen((tmp)[j]));
			if (strncmp > 0)
			{
				tmp_2 = (tmp)[i];
				(tmp)[i] = (tmp)[j];
				(tmp)[j] = tmp_2;
			}
		}
	}
	return (0);
}

void	print_env(char **a)
{
	int	i;

	i = -1;
	while (a && a[++i])
		ft_putmatrix_fd(a, 1, 1);
}

//sort env alphabetically & display env with declare -x
int	sort_display_env(char **a)
{
	int	i;

	i = -1;
	if (!a)
		return (-1);
	sort(a);
	while (a && a[++i])
		printf("declare -x %s\n", a[i]);
	return (0);
}

int	mini_export(t_prompt *prompt)
{
	int		ij[2];
	int		pos;
	char	**argv;

	argv = ((t_mini *)prompt->cmds->content)->full_cmd;
	if (ft_matrixlen(argv) > 1)
	{
		ij[0] = 1;
		while (argv[ij[0]])
		{
			pos = var_in_envp(argv[ij[0]], prompt->envp, ij);
			if (pos == 1)
			{
				free(prompt->envp[ij[1]]);
				prompt->envp[ij[1]] = ft_strdup(argv[ij[0]]);
			}
			else if (!pos)
				prompt->envp = ft_extend_matrix(prompt->envp, argv[ij[0]]);
			ij[0]++;
		}
	}
	if (!argv[1])
		sort_display_env(prompt->envp);
	return (0);
}
