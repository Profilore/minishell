/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavinia <nlavinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:01:48 by nlavinia          #+#    #+#             */
/*   Updated: 2022/06/18 13:11:03 by nlavinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	cnt;

	str = (char *)malloc(sizeof(*s1) * (ft_strlen((char *)s1) + 1));
	if (!str)
		return (NULL);
	cnt = 0;
	while (s1[cnt])
	{
		str[cnt] = s1[cnt];
		cnt++;
	}
	str[cnt] = 0;
	return (str);
}
