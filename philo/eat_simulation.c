/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahkaya <bahkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 14:35:35 by bahkaya           #+#    #+#             */
/*   Updated: 2026/06/21 14:35:35 by bahkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_data *data)
{
	int	end;

	pthread_mutex_lock(&data->death_mutex);
	end = data->simulation_end;
	pthread_mutex_unlock(&data->death_mutex);
	return (end);
}

void	printf_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!is_dead(philo->data))
		printf("%ld %d %s\n", get_current_time()
			- philo->data->start_time, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	philo_eats(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	printf_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	printf_status(philo, "is eating");
}

void	*routine(void *all)
{
	t_philo	*philo;

	philo = (t_philo *)all;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->data->nb_philos == 1)
	{
		printf_status(philo, "has taken taken a fork");
		ft_usleep(philo->data->time_to_die, philo->data);
		return (NULL);
	}
	while (!is_dead(philo->data))
	{
		if (is_dead(philo->data))
			return (NULL);
		philo_eats(philo);
		ft_usleep(philo->data->time_to_eat, philo->data);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		printf_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, philo->data);
		printf_status(philo, "is thinking");
	}
	return (NULL);
}

void	*waiter_routine(void *all)
{
	t_data	*data;
	t_philo	*current;
	int		all_full;

	data = (t_data *)all;
	usleep(100);
	while (!is_dead(data))
	{
		current = data->philos;
		all_full = 0;
		while (current && !is_dead(data))
		{
			pthread_mutex_lock(&current->meal_mutex);
			ft_death_musteat_check(current, &all_full);
			current = current->next;
		}
		all_have_eaten(data, &all_full);
		usleep (100);
	}
	return (NULL);
}
