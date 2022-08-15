/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavinia <nlavinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:01:48 by nlavinia          #+#    #+#             */
/*   Updated: 2022/06/18 13:13:36 by nlavinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t symb)
{
	size_t	needlen;

	needlen = ft_strlen((char *)needle);
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && needlen <= symb)
	{
		if (*haystack == *needle && ft_memcmp(haystack, needle, needlen) == 0)
		{
			return ((char *)haystack);
		}
		else
		{
			haystack++;
			symb--;
		}
	}
	return (NULL);
}
