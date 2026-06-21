#include "philo.h"

int is_dead(t_data *data)
{
	int end;

	pthread_mutex_lock(&data->death_mutex);
	end = data->simulation_end;
	pthread_mutex_unlock(&data->death_mutex);
	return (end);
}

void	printf_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!is_dead(philo->data))
		printf("%ld %d %s\n", get_current_time() - philo->data->start_time, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
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

void	*routine(void *all)
{
	t_philo *philo;
	philo = (t_philo *)all;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->data->nb_philos == 1)
	{
		printf_status(philo, "has taken left fork");
		ft_usleep(philo->data->time_to_die, philo->data);
		return (NULL);
	}
	while(!is_dead(philo->data))
	{

		printf_status(philo, "is thinking");
		if(is_dead(philo->data))
			return(NULL);
		pthread_mutex_lock(philo->left_fork);
		printf_status(philo, "has taken left fork");

		pthread_mutex_lock(philo->right_fork);
		printf_status(philo, "has taken right fork");

		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = get_current_time();
		philo->meals_eaten++;
		printf_status(philo, "is eating");
		pthread_mutex_unlock(&philo->meal_mutex);

		ft_usleep(philo->data->time_to_eat, philo->data);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		printf_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, philo->data);
	}
	return(NULL);
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
		while (current)
		{
			pthread_mutex_lock(&current->meal_mutex);
			if (current->last_meal != 0 && get_current_time() - current->last_meal > data->time_to_die)
			{
				pthread_mutex_unlock(&current->meal_mutex);
				pthread_mutex_lock(&data->print_mutex);
				printf("%ld %d has died\n", get_current_time() - data->start_time, current->id);
				pthread_mutex_unlock(&data->print_mutex);
				pthread_mutex_lock(&data->death_mutex);
				data->simulation_end = 1;
				pthread_mutex_unlock(&data->death_mutex);
				return (NULL);
			}
			if (data->must_eat_count != -1 && current->meals_eaten >= data->must_eat_count)
				all_full++;
			pthread_mutex_unlock(&current->meal_mutex);
			current = current->next;
		}
		if (data->must_eat_count != -1 && all_full == data->nb_philos)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->simulation_end = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

int	ft_create_mutexes(t_data *data)
{
	int	i;
	t_philo *current_philo;

	current_philo = data->philos;
	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if(!data->forks)
		return (0);
	if(pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return(0);
	if(pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return(0);
	while(i < data->nb_philos)
	{
		if(pthread_mutex_init(&data->forks[i], NULL) != 0)
			return(0);
		i++;
	}
	while (current_philo)
	{
		if(pthread_mutex_init(&current_philo->meal_mutex, NULL) != 0)
			return(0);
		current_philo = current_philo->next;
	}
	return(1);
}

int	assign_forks(t_data *data)
{
	t_philo	*current_philo;
	size_t	i;

	i = 0;
	current_philo = data->philos;
	while(current_philo)
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
	return(1);
}

int	ft_create_thread(t_data *data)
{
	t_philo	*current_philo;

	if(pthread_create(&data->waiter_thread, NULL, waiter_routine, data) != 0)
		return (0);
	current_philo = data->philos;
	while(current_philo)
	{
		if(pthread_create(&current_philo->thread, NULL, routine, current_philo) != 0)
			return (0);
		current_philo = current_philo->next;
	}
	return(1);
}
int ft_join_philos(t_data *data)
{
	t_philo *current;

	if(pthread_join(data->waiter_thread, NULL) != 0)
		return (0);
	current = data->philos;
	while(current)
	{
		if(pthread_join(current->thread, NULL) != 0)
			return (0);
		current = current->next;
	}
	return (1);
}