/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_destroy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahkaya <bahkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 12:48:11 by bahkaya           #+#    #+#             */
/*   Updated: 2026/06/21 15:50:36 by bahkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_next(t_data *data, t_philo *new_philo)
{
	t_philo	*current;

	current = new_philo;
	if (data->philos == NULL)
		data->philos = new_philo;
	else
	{
		current = data->philos;
		while (current->next != NULL)
			current = current->next;
		current->next = new_philo;
	}
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
		data->must_eat_count = ft_atoi_int(av[5]);
	data->simulation_end = 0;
	data->start_time = get_current_time();
	data->philos = NULL;
	return (data);
}

int	allocate_philos(t_data *data)
{
	int		i;
	t_philo	*new_philo;

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
		philo_next(data, new_philo);
		i++;
	}
	return (1);
}

void	free_data(t_data *data)
{
	t_philo	*current;
	t_philo	*tmp;
	int		i;

	if (!data)
		return ;
	current = data->philos;
	while (current)
	{
		tmp = current->next;
		pthread_mutex_destroy(&current->meal_mutex);
		free(current);
		current = tmp;
	}
	if (data->forks)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data);
}
