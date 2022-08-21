/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavinia <nlavinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:01:48 by nlavinia          #+#    #+#             */
/*   Updated: 2022/06/18 13:10:04 by nlavinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	cnt;
	char	*dst_ch;
	char	*src_ch;

	if (n != 0 && !src && !dst)
		return (NULL);
	cnt = 0;
	dst_ch = (char *)dst;
	src_ch = (char *)src;
	while (cnt < n)
	{
		dst_ch[cnt] = src_ch[cnt];
		cnt++;
	}
	return (dst);
}
