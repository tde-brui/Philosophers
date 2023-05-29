/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 09:49:36 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/05/29 20:25:19 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(pthread_mutex_t *forks, t_philo *philo, int num_of_philos, char **argv)
{
	int				i;
	struct timeval	tv;

	i = 0;
	init_forks(forks, num_of_philos);
	gettimeofday(&tv, NULL);
	while (i < num_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].num_meals = 0;
		philo[i].num_of_philos = num_of_philos;
		philo[i].time_to_die = ft_atoi(argv[2]) * 1000;
		philo[i].time_to_eat = ft_atoi(argv[3]) * 1000;
		philo[i].time_to_sleep = ft_atoi(argv[4]) * 1000;
		philo[i].max_meals = ft_atoi(argv[5]);
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % num_of_philos];
		philo[i].start_time = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
		philo[i].curr_time = 0;
		i++;
	}
	return (EXIT_SUCCESS);
}

void	think(pthread_mutex_t *p_lock, t_philo *philo)
{
	long long	curr_time;

	pthread_mutex_lock(p_lock);
	curr_time = time_diff(philo->start_time);
	printf("%lld %d is thinking\n", curr_time, philo->id);
	pthread_mutex_unlock(p_lock);
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
		if (philo->num_meals > 0)
			think(&p_lock, philo);
		forks_up(&p_lock, philo);
		if (eat(&p_lock, philo))
			break ;
		forks_down(philo);
		if (philo->num_meals == philo->max_meals - 1)
			break ;
		sleepy(p_lock, philo);
		philo->num_meals++;
	}
	pthread_mutex_destroy(&p_lock);
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
	free(threads);
	return (EXIT_SUCCESS);
}

void	ft_leaks(void)
{
	system("leaks philo");
}

int	input_val(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc != 6)
	{
		printf("This program takes 5 arguments\n");
		return (EXIT_FAILURE);
	}
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Arguments can only consist of digits\n");
				return (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	free_philos_and_forks(t_philo *philo, pthread_mutex_t *forks)
{
	free(philo);
	free(forks);
}

int	main(int argc, char **argv)
{
	int				num_of_philos;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	
	if (input_val(argc, argv))
		return (EXIT_FAILURE);
	num_of_philos = ft_atoi(argv[1]);
	forks = malloc(sizeof(pthread_mutex_t) * num_of_philos);
	if (!forks)
		return (EXIT_FAILURE);
	philo = malloc(num_of_philos * sizeof(t_philo));
	if (!philo)
		return (EXIT_FAILURE);
	init_philos(forks, philo, num_of_philos, argv);
	create_philos(philo, num_of_philos);
	free_philos_and_forks(philo, forks);
	//atexit(ft_leaks);
	return (EXIT_SUCCESS);
}
