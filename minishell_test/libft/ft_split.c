/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavinia <nlavinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:01:48 by nlavinia          #+#    #+#             */
/*   Updated: 2022/06/18 13:10:53 by nlavinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_mass(char **mass)
{
	int		j;

	j = 0;
	while (mass[j] != NULL)
	{
		free (mass[j]);
		j++;
	}
	free (mass);
}

static char	*malloc_part(char *s, char c)
{
	char	*part;
	int		cnt;

	cnt = 0;
	part = NULL;
	while (s[cnt] != '\0' && s[cnt] != c)
		cnt++;
	part = malloc(sizeof(char) * (cnt + 1));
	if (!part)
		return (NULL);
	cnt = 0;
	while (s[cnt] != '\0' && s[cnt] != c)
	{
		part[cnt] = s[cnt];
		cnt++;
	}
	part[cnt] = '\0';
	return (part);
}

static size_t	cnt_parts(char *s, char c)
{
	size_t	cnt;
	size_t	i;

	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
			cnt++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (cnt);
}

static char	**cut_part(char **mass, char *s, char c)
{
	size_t	cnt;
	size_t	j;

	j = 0;
	cnt = 0;
	while (s[cnt] != '\0')
	{
		while (s[cnt] != '\0' && s[cnt] == c)
			cnt++;
		if (s[cnt] != '\0' && s[cnt] != c)
		{
			mass[j] = NULL;
			mass[j] = malloc_part((char *)s + cnt, c);
			if (mass[j] == NULL)
			{	
				free_mass(mass);
				return (NULL);
			}
			j++;
		}
		while (s[cnt] != '\0' && s[cnt] != c)
			cnt++;
	}
	mass[j] = NULL;
	return (mass);
}

char	**ft_split(char const *s, char c)
{
	char	**mass;

	mass = NULL;
	if (!s)
		return (NULL);
	mass = (char **)malloc(sizeof(char *) * (cnt_parts((char *)s, c) + 1));
	if (!mass)
		return (NULL);
	cut_part(mass, (char *)s, c);
	if (mass == NULL)
		return (NULL);
	return (mass);
}
