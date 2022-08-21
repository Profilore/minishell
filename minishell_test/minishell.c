#include "minishell.h"



int	chck_exit(char *str)
{
	if (!ft_strncmp("exit", str, 4))
		if (!str[4])
			return (0);
	return (1);
}

int	main()
{
	char	*line;

	line = readline(BEGIN(49, 34)"Myshell $> "CLOSE);
	if (!line)
		exit(0);
	while (chck_exit(line))
	{
		add_history(line);
		printf("%s\n", line);
		free(line);
		line = readline(BEGIN(49, 34)"Myshell $> "CLOSE);
	}
	free(line);
	return (0);
}
