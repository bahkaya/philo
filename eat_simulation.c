#include "philo.h"

void	printf_status(t_philo *philo, char *status)
{
	printf("%ld %d %s\n", get_current_time() - philo->data->start_time, philo->id, status);
}
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
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
	while(1)
	{
		if(get_current_time() - philo->data->start_time > philo->data->time_to_die)
		{
			printf_status(philo, "has died");
			return(0);
		}
		printf_status(philo, "is thinking");
		pthread_mutex_lock(philo->left_fork);
		printf_status(philo, "has taken left fork");
		pthread_mutex_lock(philo->right_fork);
		printf_status(philo, "has taken right fork");
		printf_status(philo, "is eating");
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
	}
	return(NULL);
}

int	ft_create_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if(!data->forks)
		return (0);
	while(i < data->nb_philos)
	{
		if(pthread_mutex_init(&data->forks[i], NULL) != 0)
			return(0);
		i++;
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
		current_philo->left_fork = &data->forks[i];
		current_philo->right_fork = &data->forks[(i + 1) % data->nb_philos];
		current_philo = current_philo->next;
		i++;
	}
	return(1);
}

int	ft_create_thread(t_data *data)
{
	t_philo	*current_philo;

	current_philo = data->philos;
	while(current_philo)
	{
		if(pthread_create(&current_philo->thread, NULL, routine, current_philo) != 0)
			exit(0);
		current_philo = current_philo->next;
	}
	return(1);
}
int ft_join_philos(t_data *data)
{
	t_philo *current;

	current = data->philos;
	while(current)
	{
		if(pthread_join(current->thread, NULL) != 0)
			return (0);
		current = current->next;
	}
	return (1);
}