/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavinia <nlavinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:01:48 by nlavinia          #+#    #+#             */
/*   Updated: 2022/06/18 13:13:13 by nlavinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	len1;
	unsigned int	len2;
	unsigned int	i;

	len1 = ft_strlen(dst);
	len2 = ft_strlen((char *)src);
	i = 0;
	if (size < len1 + 1)
		return (len2 + size);
	if (size > len1 + 1)
	{
		while (src[i] != '\0' && len1 + 1 + i < size)
		{
			dst[len1 + i] = src[i];
			i++;
		}
	}
	dst[len1 + i] = '\0';
	return (len1 + len2);
}
