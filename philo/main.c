/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahkaya <bahkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 10:44:52 by bahkaya           #+#    #+#             */
/*   Updated: 2026/06/02 10:44:52 by bahkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int philo_check(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Error in av \n");
		return (0);
	}
	if(!check_av(&av[1]))
	{
		printf("Error in digits\n");
		return (0);
	}
	if(!check_value(&av[1]))
	{
		printf("Error in values\n");
		return (0);
	}
	return (1);
}

static int	run_simulation(t_data *data)
{
	if (!allocate_philos(data))
		return (0);
	if (!ft_create_mutexes(data))
		return (0);
	if (!assign_forks(data))
		return (0);
	if (!ft_create_thread(data))
		return (0);
	if (!ft_join_philos(data))
		return (0);
	return (1);
}
 
int	main(int ac, char **av)
{
	t_data	*data;
 
	if (!philo_check(ac, av))
		return (1);
	data = allocate_data(av);
	if (!data)
		return (1);
	if (!run_simulation(data))
	{
		free_data(data);
		return (1);
	}
	free_data(data);
	return (0);
}
 
