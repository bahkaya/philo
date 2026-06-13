/*#include "philo.h"
#include <sys/time.h>*/
#include <stdio.h>
/*typedef struct s_time
{
	time_t tv_sec;
	suseconds_t tv_sec;
}	t_time;

void *ft_strlen()
{
	pthread_mutex_lock(&m1);
	int a;
	a = 0;
	while(a != 1000000)
	{
		a++;
		i++;
	}
	pthread_mutex_unlock(&m1);
	return (NULL);
}*/
int main()
{
	/*pthread_t t1;
	pthread_t t2;
	pthread_mutex_init(&m1, NULL);
	pthread_create(&t1, NULL, ft_strlen, NULL);
	pthread_create(&t2, NULL, ft_strlen, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("%d\n", i);*/
	int i;
	i = 1;
	i = i % 2;
	printf("%d\n", i);
	return(0);
}