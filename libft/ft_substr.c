/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavinia <nlavinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:01:48 by nlavinia          #+#    #+#             */
/*   Updated: 2022/06/18 13:12:47 by nlavinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	cnt;
	size_t	str_len;

	sub = NULL;
	cnt = 0;
	if (!s)
		return (NULL);
	str_len = ft_strlen((char *)s);
	if (str_len < len)
		len = str_len;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	cnt = 0;
	if (start < str_len)
		while (cnt < len && s[start])
			sub[cnt++] = s[start++];
	sub[cnt] = '\0';
	return (sub);
}
