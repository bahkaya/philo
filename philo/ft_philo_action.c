/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahkaya <bahkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 13:47:55 by bahkaya           #+#    #+#             */
/*   Updated: 2026/06/21 14:03:48 by bahkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_death_musteat_check(t_philo *current, int *all_full)
{
			if (current->last_meal != 0 && get_current_time() - current->last_meal > current->data->time_to_die)
			{
				pthread_mutex_unlock(&current->meal_mutex);
				pthread_mutex_lock(&current->data->print_mutex);
				printf("%ld %d died\n", get_current_time() - current->data->start_time, current->id);
				pthread_mutex_unlock(&current->data->print_mutex);
				pthread_mutex_lock(&current->data->death_mutex);
				current->data->simulation_end = 1;
				pthread_mutex_unlock(&current->data->death_mutex);
			}
			if (current->data->must_eat_count != -1 && current->meals_eaten >= current->data->must_eat_count)
				*all_full += 1;
			pthread_mutex_unlock(&current->meal_mutex);
}
