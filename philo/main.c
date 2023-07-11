/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 09:49:36 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/07/11 16:16:50 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_info(t_philo *philo, char **argv)
{
	struct timeval	tv;
	pthread_mutex_t	p_lock;
	pthread_mutex_t	i_lock;
	pthread_mutex_t	m_lock;
	int				i;

	pthread_mutex_init(&p_lock, NULL);
	pthread_mutex_init(&i_lock, NULL);
	pthread_mutex_init(&m_lock, NULL);
	i = 0;
	gettimeofday(&tv, NULL);
	while (argv[i])
		i++;
	philo->info->time_to_die = ft_atoi(argv[2]);
	philo->info->time_to_eat = ft_atoi(argv[3]) * 1000;
	philo->info->time_to_sleep = ft_atoi(argv[4]) * 1000;
	philo->info->max_meals = -1;
	if (i == 6)
		philo->info->max_meals = ft_atoi(argv[5]);
	philo->info->start_time = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
	philo->info->finished = 0;
	philo->info->died = false;
	philo->info->death_lock = i_lock;
	philo->info->p_lock = p_lock;
	philo->info->monitor_lock = m_lock;
}

int	init_philos(pthread_mutex_t *forks, t_philo *philo, int num, char **argv)
{
	int				i;
	t_info			*info;

	i = 0;
	info = malloc(sizeof(t_info));
	if (!info)
		return (EXIT_FAILURE);
	init_forks(forks, num);
	while (i < num)
	{
		philo[i].id = i + 1;
		philo[i].num_of_philos = num;
		philo[i].compiled_time = 0;
		philo[i].num_meals = 0;
		philo[i].curr_time = 0;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % num];
		philo[i].info = info;
		i++;
	}
	init_info(philo, argv);
	return (EXIT_SUCCESS);
}

void	*philos_main(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_usleep(philo->info->time_to_eat);
	while (compare_meals(philo) && !has_died(philo))
	{
		if (compare_eat_num(philo))
			think(philo);
		forks_up(philo);
		eat(philo);
		forks_down(philo);
		pthread_mutex_lock(&philo->info->p_lock);
		if (philo->num_meals == philo->info->max_meals - 1)
		{
			pthread_mutex_unlock(&philo->info->p_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->info->p_lock);
		if (philo->num_meals != philo->info->max_meals)
			sleepy(philo);
		add_to_meals(philo);
	}
	add_to_finished(philo);
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
		if (num_of_philos == 1)
			(pthread_create(threads + i, NULL, &onephilo, philo + i));
		else if (pthread_create(threads + i, NULL, &philos_main, philo + i))
			return (detach_threads(i, threads));
		i++;
	}
	i = 0;
	monitoring(philo, num_of_philos);
	while (i < num_of_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	return (EXIT_SUCCESS);
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
		return (free(forks), EXIT_FAILURE);
	if (init_philos(forks, philo, num_of_philos, argv))
		return (free_philos_and_forks(philo, forks), EXIT_FAILURE);
	if (create_philos(philo, num_of_philos))
	{
		destroy_mutexes(philo, num_of_philos);
		return (free_everything(philo, forks), EXIT_FAILURE);
	}
	destroy_mutexes(philo, num_of_philos);
	free_everything(philo, forks);
	return (EXIT_SUCCESS);
}
