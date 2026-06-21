/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahkaya <bahkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:12:09 by bahkaya           #+#    #+#             */
/*   Updated: 2026/06/02 12:12:09 by bahkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	check_av(char **av)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (av[i] != NULL)
	{
		k = 0;
		while (av[i][k] != '\0')
		{
			if (!ft_isdigit(av[i][k]))
				return (0);
			k++;
		}
		i++;
	}
	return (1);
}

int	check_value(char **av)
{
	size_t	i;

	i = 0;
	while (av[i] != NULL)
	{
		ft_atoi_long(av[i]);
		i++;
	}
	return (1);
}
