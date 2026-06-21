/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahkaya <bahkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 13:52:19 by bahkaya           #+#    #+#             */
/*   Updated: 2026/06/21 13:52:26 by bahkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(size_t milliseconds, t_data *data)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->simulation_end == 1)
		{
			pthread_mutex_unlock(&data->death_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->death_mutex);
		usleep(500);
	}
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
