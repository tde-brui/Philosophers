/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 09:49:36 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/05/19 16:10:46 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_philo *philo, int num_of_philos, char **argv)
{
	int				i;
	pthread_mutex_t	*forks;
	
	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * num_of_philos);
	if (!forks)
		return (EXIT_FAILURE);
	init_forks(forks, num_of_philos);
	while (i < num_of_philos)
	{
		philo[i].id = i;
		philo[i].num_meals = 0;
		philo[i].num_of_philos = num_of_philos;
		philo[i].time_to_die = ft_atoi(argv[2]) * 1000;
		philo[i].time_to_eat = ft_atoi(argv[3]) * 1000;
		philo[i].time_to_sleep = ft_atoi(argv[4]) * 1000;
		philo[i].max_meals = ft_atoi(argv[5]);
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % num_of_philos];
		i++;
	}
	return (EXIT_SUCCESS);
}

void	*philos_main_loop(void *arg)
{
	t_philo	*philo;
	pthread_mutex_t	mutex;

	philo = (t_philo *)arg;
	pthread_mutex_init(&mutex, NULL);
	while (philo->num_meals < philo->max_meals)
	{
		pthread_mutex_lock(&mutex);
		pthread_mutex_lock(philo->left_fork);
		printf("%d has taken left fork!\n", philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%d has taken right fork!\n", philo->id);
		pthread_mutex_unlock(&mutex);
		
		printf("%d is eating\n", philo->id);
		usleep(philo->time_to_eat);

		pthread_mutex_unlock(philo->left_fork);
		printf("%d has put down left fork\n", philo->id);
		pthread_mutex_unlock(philo->right_fork);
		printf("%d has put down right fork\n", philo->id);

		printf("%d is sleeping\n", philo->id);
		usleep(philo->time_to_sleep);
		
		philo->num_meals++;
	}
	printf("Philosopher %d has finished eating!\n", philo->id);
	return (EXIT_SUCCESS);
}

int	create_philos(t_philo *philo, int num_of_philos)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * num_of_philos);
	if (!threads)
		return (EXIT_FAILURE);
	while (i < num_of_philos)
	{
		pthread_create(threads + i, NULL, &philos_main_loop, philo + i);
		i++;
	}
	i = 0;
	while (i < num_of_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	int		num_of_philos;
	t_philo	*philo;

	num_of_philos = ft_atoi(argv[1]);
	philo = malloc(num_of_philos * sizeof(t_philo));
	if (!philo)
		return (EXIT_FAILURE);
	if (argc != 6)
		return (EXIT_FAILURE);
	init_philos(philo, num_of_philos, argv);
	create_philos(philo, num_of_philos);
	//printf("%d\n", philo[3].time_to_die);
	return (EXIT_SUCCESS);
}
