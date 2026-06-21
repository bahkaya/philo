/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_mutex_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahkaya <bahkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 13:25:04 by bahkaya           #+#    #+#             */
/*   Updated: 2026/06/21 21:00:34 by bahkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	other_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->ready_mutex, NULL) != 0)
		return (0);
	return (1);
}

static int	init_philo_mutexes(t_data *data)
{
	t_philo	*current_philo;
	int		i;

	current_philo = data->philos;
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	while (current_philo)
	{
		if (pthread_mutex_init(&current_philo->meal_mutex, NULL) != 0)
			return (0);
		current_philo = current_philo->next;
	}
	return (1);
}

int	ft_create_mutexes(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (0);
	if (!other_mutexes(data))
		return (0);
	if (!init_philo_mutexes(data))
		return (0);
	return (1);
}

int	ft_create_thread(t_data *data)
{
	t_philo	*current_philo;

	current_philo = data->philos;
	while (current_philo)
	{
		if (pthread_create(&current_philo->thread, NULL,
				routine, current_philo) != 0)
			return (0);
		current_philo = current_philo->next;
	}
	while (!data->all_ready)
		usleep(100);
	if (pthread_create(&data->waiter_thread, NULL,
			third_party_check, data) != 0)
		return (0);
	return (1);
}

int	ft_join_philos(t_data *data)
{
	t_philo	*current;

	if (pthread_join(data->waiter_thread, NULL) != 0)
		return (0);
	current = data->philos;
	while (current)
	{
		if (pthread_join(current->thread, NULL) != 0)
			return (0);
		current = current->next;
	}
	return (1);
}
