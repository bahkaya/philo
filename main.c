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

int main(int ac, char **av)
{
	t_data *data;
	if (ac != 5 && ac != 6)
	{
		printf("Error in av \n");
		return (1); // av control
	}
	if(!check_av(&av[1]))
	{
		printf("Error in digits\n");
		return (1);
	}
	check_value(&av[1]);
	data = allocate_data(av);
	if(!data)
		return(1);
	if(!allocate_philos(data))
		return(1);
	if(!ft_create_mutexes(data))
		return(1);
	if(!assign_forks(data))
		return(1);
	if(!ft_create_thread(data))
		return(1);
	if(!ft_join_philos(data))
		return(1);
	return(0);
}
