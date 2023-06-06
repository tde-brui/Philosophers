/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 09:49:36 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/06/06 17:45:11 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(pthread_mutex_t *forks, t_philo *philo, int num_of_philos, char **argv)
{
	int				i;
	struct timeval	tv;
	t_info			*info;
	pthread_mutex_t	p_lock;
	pthread_mutex_t	i_lock;

	i = 0;
	init_forks(forks, num_of_philos);
	gettimeofday(&tv, NULL);
	info = malloc(sizeof(t_info));
	if (!info)
		return (EXIT_FAILURE);
	pthread_mutex_init(&p_lock, NULL);
	pthread_mutex_init(&i_lock, NULL);
	while (i < num_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].num_meals = 0;
		philo[i].num_of_philos = num_of_philos;
		philo[i].curr_time = 0;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % num_of_philos];
		philo[i].info = info;
		i++;
	}
	philo->info->time_to_die = ft_atoi(argv[2]) * 1000;
	philo->info->time_to_eat = ft_atoi(argv[3]) * 1000;
	philo->info->time_to_sleep = ft_atoi(argv[4]) * 1000;
	philo->info->max_meals = ft_atoi(argv[5]);
	philo->info->start_time = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
	philo->info->i = 0;
	philo->info->p_lock = p_lock;
	philo->info->i_lock = i_lock;
	return (EXIT_SUCCESS);
}

void	*philos_main_loop(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_usleep(50);
	while (philo->num_meals < philo->info->max_meals && philo->info->i == 0)
	{
		if (philo->num_meals > 0)
			think(philo);
		forks_up(philo);
		if (eat(philo))
			break ;
		forks_down(philo);
		if (philo->num_meals == philo->info->max_meals - 1)
			break ;
		sleepy(philo);
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
		return (free_everything(philo, forks), EXIT_FAILURE);
	free_everything(philo, forks);
	return (EXIT_SUCCESS);
}
