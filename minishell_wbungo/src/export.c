
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
//add string: "declare -x "
char *add_declare(char *str)
{
	char	*newstr;
	int		len;

//	len = ft_strlen(str);
//	printf("str_len=%d\n", len);
	newstr = malloc(ft_strlen("declare -x ") + ft_strlen(str) + 1);
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, "declare -x ", (ft_strlen("declare -x ") + 1));
//	printf("newstr=|%s|\n|", newstr);
	len = ft_strlen(newstr) + ft_strlen(str) + 1;
//	printf("new len=%d\n", len);
	ft_strlcat(newstr, str, len );
//	printf("newstr=|%s|\n|", newstr);
//	len = ft_strlen(newstr);
//	printf("new len=%d\n", len);

	return (newstr);
}
//sort env alphabetically & display env with declare -x
int	sort_display_env(char **a)
{
	int		i;
	char	**tmp;
	size_t	strlen;

	i = -1;
	strlen = 0;
	if (!a)
		return (-1);
	tmp = ft_dup_matrix(a);
	sort(tmp);
//	print_env(argv);
	while(a && a[++i])
	{
//		printf("%s\n", a[i]);
		strlen = ft_strlen(tmp[i]) + ft_strlen("declare -x ");
//		printf("sort_display_env strlen=%zu\n", strlen);
		a[i] = add_declare(tmp[i]);
		printf("%s\n", a[i]);
	}
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
	prompt->declare = ft_dup_matrix(prompt->envp);
//new function for EXPORT without args
//to alphabetical sort and then display env	
	if (!argv[1])
//		sort_display_env(tmp);
//		sort_display_env(prompt->envp);
		sort_display_env(prompt->declare);
	return (0);
}

