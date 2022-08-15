/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavinia <nlavinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:01:48 by nlavinia          #+#    #+#             */
/*   Updated: 2022/06/18 13:13:17 by nlavinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size)
{
	size_t	cnt;

	cnt = 0;
	if (dst_size > 0)
	{
		while (src[cnt] != '\0' && cnt < (dst_size - 1))
		{
			dst[cnt] = src[cnt];
			cnt++;
		}
		dst[cnt] = '\0';
	}
	cnt = ft_strlen((char *)src);
	return (cnt);
}
