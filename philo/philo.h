/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahkaya <bahkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 14:27:30 by bahkaya           #+#    #+#             */
/*   Updated: 2026/06/21 14:27:30 by bahkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data
{
	int				nb_philos;

	long unsigned	time_to_die;

	long			time_to_eat;

	long			time_to_sleep;

	int				must_eat_count;

	int				simulation_end;

	long			start_time;

	pthread_mutex_t	*forks;

	pthread_mutex_t	print_mutex;

	pthread_mutex_t	death_mutex;

	pthread_t		waiter_thread;

	struct s_philo	*philos;

}	t_data;

typedef struct s_philo
{
	int				id;

	int				meals_eaten;

	long			last_meal;

	pthread_t		thread;

	pthread_mutex_t	meal_mutex;

	pthread_mutex_t	*left_fork;

	pthread_mutex_t	*right_fork;

	t_data			*data;

	struct s_philo	*next;

}	t_philo;

int		ft_isdigit(int c);
int		check_av(char **av);
int		check_value(char **av);
int		ft_atoi_int(const char *str);
long	ft_atoi_long(const char *str);
void	free_data(t_data *data);
t_data	*allocate_data(char **av);
int		allocate_philos(t_data *data);
void	*routine(void *all);
void	*waiter_routine(void *all);
int		ft_create_thread(t_data *data);
int		ft_join_philos(t_data *data);
size_t	get_current_time(void);
int		ft_create_mutexes(t_data *data);
int		assign_forks(t_data *data);
int		ft_usleep(size_t milliseconds, t_data *data);
size_t	get_current_time(void);
void	ft_death_musteat_check(t_philo *current, int *all_full);
void	all_have_eaten(t_data *data, int *all_full);
#endif