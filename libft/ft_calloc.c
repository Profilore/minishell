/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavinia <nlavinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:01:48 by nlavinia          #+#    #+#             */
/*   Updated: 2022/07/07 23:35:36 by nlavinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*aux;
	size_t	sum;

	sum = size * n;
	if (sum < n && sum < size)
		return (NULL);
	aux = malloc(n * size);
	if (aux == (void *)0)
		return (NULL);
	ft_bzero(aux, sum);
	return (aux);
}
