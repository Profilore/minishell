/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavinia <nlavinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:01:48 by nlavinia          #+#    #+#             */
/*   Updated: 2022/06/20 11:33:36 by nlavinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checklength(const char *n, int sign)
{
	char	*longmax;
	char	*longmin;
	int		max;
	int		min;
	size_t	len;

	max = 0;
	min = 0;
	len = ft_strlen((char *)n);
	if (len < 10)
		return (1);
	longmax = "2147483647";
	longmin = "2147483648";
	if (sign == 1)
		min = ft_strncmp(longmin, (char *)n, len);
	else
		max = ft_strncmp((char *)n, longmax, len);
	if (max > 0)
		return (-1);
	else if (min < 0)
		return (0);
	else
		return (1);
}

int	ft_atoi(const char *str)
{
	int	r;
	int	minus;

	r = 0;
	minus = 0;
	while (*str == ' ' || (*str > 8 && *str < 14))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		minus = 1;
		str++;
	}
	if (ft_checklength(str, minus) == 0 || ft_checklength(str, minus) == -1)
		return (ft_checklength(str, minus));
	while (*str >= '0' && *str <= '9')
	{
		r = r * 10 + *str - '0';
		str++;
	}
	if (minus)
		r = -r;
	return (r);
}
