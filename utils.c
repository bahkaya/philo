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
#include "limits.h"
int	ft_isdigit(int c)
{
	if(c >= 48 && c <= 57)
		return(1);
	else
		return(0);
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
			if(!ft_isdigit(av[i][k]))
				return(0);
			k++;
		}
		i++;
	}
	return(1);
}
int	check_value(char **av)
{
	size_t	i;
	size_t	value;

	i = 0;
	value = 0;
	while (av[i] != NULL)
	{
		value = ft_atoi_long(av[i]);
		if(value == 0 || value > LONG_MAX)
			return(0);
		i++;
	}
	return (1);
}

t_data	*allocate_data(char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	memset(data, 0, sizeof(t_data));
	data->nb_philos = ft_atoi_int(av[1]);
	data->time_to_die = ft_atoi_long(av[2]);
	data->time_to_eat = ft_atoi_long(av[3]);
	data->time_to_sleep = ft_atoi_long(av[4]);
	data->must_eat_count = -1;
	if (av[5])
		data->must_eat_count = atoi(av[5]);
	data->simulation_end = 0;
	data->start_time = get_current_time();
	data->philos = NULL;
	return (data);
}

int	allocate_philos(t_data *data)
{
	int	i;
	t_philo	*new_philo;
	t_philo	*current;

	i = 0;
	while (i < data->nb_philos)
	{
		new_philo = malloc(sizeof(t_philo));
		if (!new_philo)
			return (0);
		memset(new_philo, 0, sizeof(t_philo));
		new_philo->id = i + 1;
		new_philo->meals_eaten = 0;
		new_philo->last_meal = 0;
		new_philo->data = data;
		new_philo->next = NULL;
		if (data->philos == NULL)
			data->philos = new_philo;
		else
		{
			current = data->philos;
			while (current->next != NULL)
				current = current->next;
			current->next = new_philo;
		}
		i++;
	}
	return (1);
}
