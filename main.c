/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 09:49:36 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/05/20 17:19:34 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_philo *philo, int num_of_philos, char **argv)
{
	int				i;
	pthread_mutex_t	*forks;
	struct timeval	tv;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * num_of_philos);
	if (!forks)
		return (EXIT_FAILURE);
	init_forks(forks, num_of_philos);
	gettimeofday(&tv, NULL);
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
		philo[i].start_time = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	*philos_main_loop(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	p_lock;

	philo = (t_philo *)arg;
	pthread_mutex_init(&p_lock, NULL);
	if (philo->id % 2 != 0)
		usleep(50);
	while (philo->num_meals < philo->max_meals)
	{
		forks_up(p_lock, philo);
		if (eat(p_lock, philo))
			break ;
		forks_down(philo);
		if (philo->num_meals == philo->max_meals - 1)
			break ;
		sleepy(p_lock, philo);
		philo->num_meals++;
	}
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
	return (EXIT_SUCCESS);
}
