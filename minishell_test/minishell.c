#include "minishell.h"
#include "libft/libft.h"


int	chck_exit(char *str)
{
	if (!ft_strncmp("exit", str, 4))
		if (!str[4])
			return (0);
	return (1);
}

int	chck_exit1(char *str)
{
	if (!ft_strncmp("exit 1", str, 6))
		if (!str[6])
			return(0);
	return(1);
}

int	main()
{
	char	*line;

	line = readline(BEGIN(49, 34)"Myshell $> "CLOSE);
	if (!line)
		exit(0);
	while (chck_exit(line) && chck_exit1(line))
	{
		add_history(line);
		printf("%s\n", line);
		free(line);
		line = readline(BEGIN(49, 34)"Myshell $> "CLOSE);
	}
	if (!chck_exit1(line))
	{
		free(line);
		exit(1);
	}
	free(line);
	return (0);
}
