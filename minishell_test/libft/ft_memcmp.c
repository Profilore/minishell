/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavinia <nlavinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:01:48 by nlavinia          #+#    #+#             */
/*   Updated: 2022/06/18 13:09:59 by nlavinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	cnt;
	char	*s1i;
	char	*s2i;

	s1i = (char *)s1;
	s2i = (char *)s2;
	cnt = 0;
	if (n == 0)
		return (0);
	while (cnt < n)
	{
		if (s1i[cnt] == s2i[cnt])
			cnt++;
		else
			return ((unsigned char)s1i[cnt] - (unsigned char)s2i[cnt]);
	}
	return (0);
}
