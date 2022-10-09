
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
//	printf("sort\n");
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
	while(a && a[++i])
	{
//		printf("declare -x %s\n", a[i]);
		ft_putmatrix_fd(a, 1, 1);

	}
}

//sort env alphabetically & display env with declare -x
int	sort_display_env(char **a)
{
	int	i;

	i = -1;
	if (!a)
		return (-1);
	sort(a);
//	print_env(argv);
	while(a && a[++i])
		printf("declare -x %s\n", a[i]);
	return (0);
}

int	mini_export(t_prompt *prompt)
{
	int		ij[2];
	int		pos;
	char	**argv;
//debug
//	int		matrixlen;	

	argv = ((t_mini *)prompt->cmds->content)->full_cmd;
//debug	
	printf("mini_export_starts\n");
//	print_a(argv);
//	matrixlen = ft_matrixlen(argv);
//	printf("matrixlen=\t%d\n", matrixlen);

	if (ft_matrixlen(argv) > 1)
	{
		ij[0] = 1;
//debug		
//		printf("argv[ij[0]]=\t%s\n", argv[ij[0]]);
	
		while (argv[ij[0]])
		{
			pos = var_in_envp(argv[ij[0]], prompt->envp, ij);
			if (pos == 1)
			{
				free(prompt->envp[ij[1]]);
				prompt->envp[ij[1]] = ft_strdup(argv[ij[0]]);
//				tmp[ij[1]] = ft_strdup(argv[ij[0]]);
			}
			else if (!pos)
//				tmp = ft_extend_matrix(prompt->envp, argv[ij[0]]);
				prompt->envp = ft_extend_matrix(prompt->envp, argv[ij[0]]);
			ij[0]++;
		}
	}
//debug
//new function for EXPORT without args
//to alphabetical sort and then display env	
	if (!argv[1])
//		sort_display_env(tmp);
		sort_display_env(prompt->envp);
	return (0);
}

