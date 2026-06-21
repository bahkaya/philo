/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahkaya <bahkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 13:47:55 by bahkaya           #+#    #+#             */
/*   Updated: 2026/06/21 20:53:02 by bahkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_death_musteat_check(t_philo *current, int *all_full)
{
	if (current->last_meal != 0 && get_current_time()
		- current->last_meal > current->data->time_to_die)
	{
		pthread_mutex_unlock(&current->meal_mutex);
		pthread_mutex_lock(&current->data->print_mutex);
		printf("%ld %d died\n", get_current_time()
			- current->data->start_time, current->id);
		pthread_mutex_unlock(&current->data->print_mutex);
		pthread_mutex_lock(&current->data->death_mutex);
		current->data->simulation_end = 1;
		pthread_mutex_unlock(&current->data->death_mutex);
		return ;
	}
	if (current->data->must_eat_count != -1
		&& current->meals_eaten >= current->data->must_eat_count)
		*all_full += 1;
	pthread_mutex_unlock(&current->meal_mutex);
}

int	assign_forks(t_data *data)
{
	t_philo	*current_philo;
	size_t	i;

	i = 0;
	current_philo = data->philos;
	while (current_philo)
	{
		if (i % 2 == 0)
		{
			current_philo->left_fork = &data->forks[i];
			current_philo->right_fork = &data->forks[(i + 1) % data->nb_philos];
		}
		else
		{
			current_philo->left_fork = &data->forks[(i + 1) % data->nb_philos];
			current_philo->right_fork = &data->forks[i];
		}
		current_philo = current_philo->next;
		i++;
	}
	return (1);
}

void	all_have_eaten(t_data *data, int *all_full)
{
	if (data->must_eat_count != -1 && *all_full == data->nb_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->simulation_end = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return ;
	}
}

int	philo_cycle_step(t_philo *philo)
	{
	if (is_dead(philo->data))
		return (0);
	if (!philo_eats(philo))
		return (0);
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	printf_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo->data);
	printf_status(philo, "is thinking");
	ft_usleep(philo->data->time_to_die - philo->data->time_to_eat - philo->data->time_to_sleep, philo->data);
	return (1);
}

void	wait_for_all_ready(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->ready_mutex);
	philo->data->ready_count++;
	if (philo->data->ready_count == philo->data->nb_philos)
		philo->data->all_ready = 1;
	pthread_mutex_unlock(&philo->data->ready_mutex);
	while (1)
	{
		pthread_mutex_lock(&philo->data->ready_mutex);
		if (philo->data->all_ready)
		{
			pthread_mutex_unlock(&philo->data->ready_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->ready_mutex);
		usleep(100);
	}
}
