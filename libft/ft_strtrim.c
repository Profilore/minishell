/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavinia <nlavinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:01:48 by nlavinia          #+#    #+#             */
/*   Updated: 2022/06/20 11:32:55 by nlavinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_settrue(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len1;
	size_t	back;
	size_t	frount;
	char	*tr;

	frount = 0;
	len1 = 0;
	if (!s1 || !set)
		return (NULL);
	back = ft_strlen((char *)s1);
	while (ft_settrue((char)s1[frount], (char *)set) != 0 && s1[frount])
		frount++;
	while (ft_settrue((char)s1[back - 1], (char *)set) != 0 && back > frount)
		back--;
	if (frount == 0 && back == ft_strlen((char *)s1))
		return (ft_strdup(s1));
	tr = (char *)malloc(sizeof(char) * (back - frount + 1));
	if (!tr)
		return (0);
	while (frount < back)
		tr[len1++] = s1[frount++];
	tr[len1] = '\0';
	return (tr);
}
