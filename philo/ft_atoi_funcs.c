/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahkaya <bahkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 10:53:07 by bahkaya           #+#    #+#             */
/*   Updated: 2026/06/21 20:37:26 by bahkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	ft_atoi_int(const char *str)
{
	size_t	i;
	int		value;
	int		sign;

	value = 0;
	i = 0;
	sign = 1;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '+')
			sign *= 1;
		else if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (value > (INT_MAX - (str[i] - '0')) / 10)
			return (-1);
		value = 10 * value + str[i] - '0';
		i++;
	}
	return (value * sign);
}

long	ft_atoi_long(const char *str)
{
	size_t	i;
	long	value;
	int		sign;

	value = 0;
	i = 0;
	sign = 1;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '+')
			sign *= 1;
		else if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (value > (LONG_MAX - (str[i] - '0')) / 10)
			return (-1);
		value = 10 * value + str[i] - '0';
		i++;
	}
	return (value * sign);
}
