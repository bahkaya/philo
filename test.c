/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahkaya <bahkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:12:09 by bahkaya           #+#    #+#             */
/*   Updated: 2026/06/02 12:12:09 by bahkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// EXAMPLE: Initialize all mutexes (forks, print_mutex, death_mutex, meal_mutex)
int	init_mutexes(t_data *data)
{
	int		i;
	t_philo	*current;

	// Allocate forks array (one fork per philosopher)
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (1);

	// Initialize all fork mutexes
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}

	// Initialize print and death mutexes
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (1);

	// Initialize meal_mutex for each philosopher
	current = data->philos;
	while (current)
	{
		if (pthread_mutex_init(&current->meal_mutex, NULL) != 0)
			return (1);
		current = current->next;
	}
	return (0);
}

// EXAMPLE: Assign left and right forks to each philosopher
int	assign_forks(t_data *data)
{
	int		i;
	t_philo	*current;

	i = 0;
	current = data->philos;
	while (current)
	{
		// Left fork is at index i
		current->left_fork = &data->forks[i];
		
		// Right fork is the next fork (circular: last philo's right = first fork)
		current->right_fork = &data->forks[(i + 1) % data->nb_philos];
		
		current = current->next;
		i++;
	}
	return (0);
}

// EXAMPLE: Philosopher's routine (simplified)
void	*philosopher_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		// Think
		printf("Philosopher %d is thinking\n", philo->id);
		usleep(100000);

		// Pick up left fork
		pthread_mutex_lock(philo->left_fork);
		printf("Philosopher %d has taken left fork\n", philo->id);

		// Pick up right fork
		pthread_mutex_lock(philo->right_fork);
		printf("Philosopher %d has taken right fork\n", philo->id);

		// Eat
		printf("Philosopher %d is eating\n", philo->id);
		usleep(100000);
		philo->meals_eaten++;

		// Put down forks
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		// Sleep
		printf("Philosopher %d is sleeping\n", philo->id);
		usleep(100000);
	}
	return (NULL);
}

// EXAMPLE: Create all philosopher threads
int	create_threads(t_data *data)
{
	t_philo *current;

	current = data->philos;
	while (current)
	{
		if (pthread_create(&current->thread, NULL, philosopher_routine, current) != 0)
			return (1);
		current = current->next;
	}
	return (0);
}

// EXAMPLE: Wait for all threads to finish
int	join_threads(t_data *data)
{
	t_philo *current;

	current = data->philos;
	while (current)
	{
		if (pthread_join(current->thread, NULL) != 0)
			return (1);
		current = current->next;
	}
	return (0);
}
