/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 09:49:36 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/05/17 13:37:30 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_philo **philo, int num_of_philos, char **argv)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * num_of_philos);
	*philo = malloc(num_of_philos * sizeof(t_philo));
	if (!philo)
		return (EXIT_FAILURE);
	while (i < num_of_philos)
	{
		(*philo)[i].id = i;
		(*philo)[i].num_meals = 0;
		(*philo)[i].num_of_philos = num_of_philos;
		(*philo)[i].time_to_die = ft_atoi(argv[2]);
		(*philo)[i].time_to_eat = ft_atoi(argv[3]);
		(*philo)[i].time_to_sleep = ft_atoi(argv[4]);
		(*philo)[i].max_meals = ft_atoi(argv[5]);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	*philos_main_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->num_meals < philo->max_meals)
	{
		//pick up left fork
		//pcik up right fork
		
		//usleep(time_to_eat)

		//put down left fork
		//put down right fork
		
		
	}
	return (EXIT_SUCCESS);
}

int	create_philos(t_philo **philo, int num_of_philos)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * num_of_philos);
	if (!threads)
		return (EXIT_FAILURE);
	while (i < num_of_philos)
	{
		pthread_create(&threads[i], NULL, &philos_main_loop, (void *)philo[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	int		num_of_philos;
	t_philo	*philo;

	num_of_philos = ft_atoi(argv[1]);
	init_philos(&philo, num_of_philos, argv);
	return (EXIT_SUCCESS);
}
